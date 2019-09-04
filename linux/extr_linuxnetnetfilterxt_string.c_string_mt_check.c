#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ v1; } ;
struct xt_string_info {scalar_t__ from_offset; scalar_t__ to_offset; char* algo; scalar_t__ patlen; struct ts_config* config; int /*<<< orphan*/  pattern; TYPE_2__ u; } ;
struct xt_mtchk_param {struct xt_string_info* matchinfo; } ;
struct ts_config {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct ts_config*) ; 
 int PTR_ERR (struct ts_config*) ; 
 int TS_AUTOLOAD ; 
 int TS_IGNORECASE ; 
 int XT_STRING_FLAG_IGNORECASE ; 
 int XT_STRING_FLAG_INVERT ; 
 int XT_STRING_MAX_ALGO_NAME_SIZE ; 
 scalar_t__ XT_STRING_MAX_PATTERN_SIZE ; 
 struct ts_config* textsearch_prepare (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int string_mt_check(const struct xt_mtchk_param *par)
{
	struct xt_string_info *conf = par->matchinfo;
	struct ts_config *ts_conf;
	int flags = TS_AUTOLOAD;

	/* Damn, can't handle this case properly with iptables... */
	if (conf->from_offset > conf->to_offset)
		return -EINVAL;
	if (conf->algo[XT_STRING_MAX_ALGO_NAME_SIZE - 1] != '\0')
		return -EINVAL;
	if (conf->patlen > XT_STRING_MAX_PATTERN_SIZE)
		return -EINVAL;
	if (conf->u.v1.flags &
	    ~(XT_STRING_FLAG_IGNORECASE | XT_STRING_FLAG_INVERT))
		return -EINVAL;
	if (conf->u.v1.flags & XT_STRING_FLAG_IGNORECASE)
		flags |= TS_IGNORECASE;
	ts_conf = textsearch_prepare(conf->algo, conf->pattern, conf->patlen,
				     GFP_KERNEL, flags);
	if (IS_ERR(ts_conf))
		return PTR_ERR(ts_conf);

	conf->config = ts_conf;
	return 0;
}