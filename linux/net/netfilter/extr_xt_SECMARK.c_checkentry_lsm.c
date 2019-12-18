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
struct xt_secmark_target_info {char* secctx; scalar_t__ secid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int SECMARK_SECCTX_MAX ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,...) ; 
 int security_secctx_to_secid (char*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  security_secmark_refcount_inc () ; 
 int security_secmark_relabel_packet (scalar_t__) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int checkentry_lsm(struct xt_secmark_target_info *info)
{
	int err;

	info->secctx[SECMARK_SECCTX_MAX - 1] = '\0';
	info->secid = 0;

	err = security_secctx_to_secid(info->secctx, strlen(info->secctx),
				       &info->secid);
	if (err) {
		if (err == -EINVAL)
			pr_info_ratelimited("invalid security context \'%s\'\n",
					    info->secctx);
		return err;
	}

	if (!info->secid) {
		pr_info_ratelimited("unable to map security context \'%s\'\n",
				    info->secctx);
		return -ENOENT;
	}

	err = security_secmark_relabel_packet(info->secid);
	if (err) {
		pr_info_ratelimited("unable to obtain relabeling permission\n");
		return err;
	}

	security_secmark_refcount_inc();
	return 0;
}