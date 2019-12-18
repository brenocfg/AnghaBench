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

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int Opt_error ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmemdup_nul (char*,int,int /*<<< orphan*/ ) ; 
 int match_opt_prefix (char*,int,char**) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int smack_add_opt (int,char*,void**) ; 
 int /*<<< orphan*/  smack_free_mnt_opts (void*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int smack_sb_eat_lsm_opts(char *options, void **mnt_opts)
{
	char *from = options, *to = options;
	bool first = true;

	while (1) {
		char *next = strchr(from, ',');
		int token, len, rc;
		char *arg = NULL;

		if (next)
			len = next - from;
		else
			len = strlen(from);

		token = match_opt_prefix(from, len, &arg);
		if (token != Opt_error) {
			arg = kmemdup_nul(arg, from + len - arg, GFP_KERNEL);
			rc = smack_add_opt(token, arg, mnt_opts);
			if (unlikely(rc)) {
				kfree(arg);
				if (*mnt_opts)
					smack_free_mnt_opts(*mnt_opts);
				*mnt_opts = NULL;
				return rc;
			}
		} else {
			if (!first) {	// copy with preceding comma
				from--;
				len++;
			}
			if (to != from)
				memmove(to, from, len);
			to += len;
			first = false;
		}
		if (!from[len])
			break;
		from += len + 1;
	}
	*to = '\0';
	return 0;
}