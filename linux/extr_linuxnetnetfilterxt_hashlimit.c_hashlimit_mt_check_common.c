#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xt_mtchk_param {int /*<<< orphan*/  family; struct net* net; } ;
struct xt_hashlimit_htable {int dummy; } ;
struct net {int dummy; } ;
struct hashlimit_cfg3 {scalar_t__ gc_interval; scalar_t__ expire; int srcmask; int dstmask; int mode; int avg; scalar_t__ interval; int burst; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 int U32_MAX ; 
 int XT_HASHLIMIT_ALL ; 
 int XT_HASHLIMIT_BYTES ; 
 int XT_HASHLIMIT_RATE_MATCH ; 
 int /*<<< orphan*/  hashlimit_mutex ; 
 int htable_create (struct net*,struct hashlimit_cfg3*,char const*,int /*<<< orphan*/ ,struct xt_hashlimit_htable**,int) ; 
 struct xt_hashlimit_htable* htable_find_get (struct net*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,...) ; 
 scalar_t__ user2credits (int,int) ; 
 scalar_t__ user2credits_byte (int) ; 

__attribute__((used)) static int hashlimit_mt_check_common(const struct xt_mtchk_param *par,
				     struct xt_hashlimit_htable **hinfo,
				     struct hashlimit_cfg3 *cfg,
				     const char *name, int revision)
{
	struct net *net = par->net;
	int ret;

	if (cfg->gc_interval == 0 || cfg->expire == 0)
		return -EINVAL;
	if (par->family == NFPROTO_IPV4) {
		if (cfg->srcmask > 32 || cfg->dstmask > 32)
			return -EINVAL;
	} else {
		if (cfg->srcmask > 128 || cfg->dstmask > 128)
			return -EINVAL;
	}

	if (cfg->mode & ~XT_HASHLIMIT_ALL) {
		pr_info_ratelimited("Unknown mode mask %X, kernel too old?\n",
				    cfg->mode);
		return -EINVAL;
	}

	/* Check for overflow. */
	if (revision >= 3 && cfg->mode & XT_HASHLIMIT_RATE_MATCH) {
		if (cfg->avg == 0 || cfg->avg > U32_MAX) {
			pr_info_ratelimited("invalid rate\n");
			return -ERANGE;
		}

		if (cfg->interval == 0) {
			pr_info_ratelimited("invalid interval\n");
			return -EINVAL;
		}
	} else if (cfg->mode & XT_HASHLIMIT_BYTES) {
		if (user2credits_byte(cfg->avg) == 0) {
			pr_info_ratelimited("overflow, rate too high: %llu\n",
					    cfg->avg);
			return -EINVAL;
		}
	} else if (cfg->burst == 0 ||
		   user2credits(cfg->avg * cfg->burst, revision) <
		   user2credits(cfg->avg, revision)) {
		pr_info_ratelimited("overflow, try lower: %llu/%llu\n",
				    cfg->avg, cfg->burst);
		return -ERANGE;
	}

	mutex_lock(&hashlimit_mutex);
	*hinfo = htable_find_get(net, name, par->family);
	if (*hinfo == NULL) {
		ret = htable_create(net, cfg, name, par->family,
				    hinfo, revision);
		if (ret < 0) {
			mutex_unlock(&hashlimit_mutex);
			return ret;
		}
	}
	mutex_unlock(&hashlimit_mutex);

	return 0;
}