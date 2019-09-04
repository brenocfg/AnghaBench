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
typedef  int u64 ;
typedef  int /*<<< orphan*/  substring_t ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_OPT_ARGS ; 
#define  NVMF_OPT_WWNN 129 
#define  NVMF_OPT_WWPN 128 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  match_u64 (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  opt_tokens ; 
 int /*<<< orphan*/  pr_warn (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
fcloop_parse_nm_options(struct device *dev, u64 *nname, u64 *pname,
		const char *buf)
{
	substring_t args[MAX_OPT_ARGS];
	char *options, *o, *p;
	int token, ret = 0;
	u64 token64;

	*nname = -1;
	*pname = -1;

	options = o = kstrdup(buf, GFP_KERNEL);
	if (!options)
		return -ENOMEM;

	while ((p = strsep(&o, ",\n")) != NULL) {
		if (!*p)
			continue;

		token = match_token(p, opt_tokens, args);
		switch (token) {
		case NVMF_OPT_WWNN:
			if (match_u64(args, &token64)) {
				ret = -EINVAL;
				goto out_free_options;
			}
			*nname = token64;
			break;
		case NVMF_OPT_WWPN:
			if (match_u64(args, &token64)) {
				ret = -EINVAL;
				goto out_free_options;
			}
			*pname = token64;
			break;
		default:
			pr_warn("unknown parameter or missing value '%s'\n", p);
			ret = -EINVAL;
			goto out_free_options;
		}
	}

out_free_options:
	kfree(options);

	if (!ret) {
		if (*nname == -1)
			return -EINVAL;
		if (*pname == -1)
			return -EINVAL;
	}

	return ret;
}