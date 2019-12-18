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
struct tomoyo_domain_info {int /*<<< orphan*/  acl_info_list; int /*<<< orphan*/  ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  TOMOYO_STAT_POLICY_UPDATES ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  tomoyo_addprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  tomoyo_normalize_line (char*) ; 
 scalar_t__ tomoyo_truncate (char*) ; 
 int /*<<< orphan*/  tomoyo_update_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tomoyo_write_domain2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void tomoyo_add_entry(struct tomoyo_domain_info *domain, char *header)
{
	char *buffer;
	char *realpath = NULL;
	char *argv0 = NULL;
	char *symlink = NULL;
	char *cp = strchr(header, '\n');
	int len;

	if (!cp)
		return;
	cp = strchr(cp + 1, '\n');
	if (!cp)
		return;
	*cp++ = '\0';
	len = strlen(cp) + 1;
	/* strstr() will return NULL if ordering is wrong. */
	if (*cp == 'f') {
		argv0 = strstr(header, " argv[]={ \"");
		if (argv0) {
			argv0 += 10;
			len += tomoyo_truncate(argv0) + 14;
		}
		realpath = strstr(header, " exec={ realpath=\"");
		if (realpath) {
			realpath += 8;
			len += tomoyo_truncate(realpath) + 6;
		}
		symlink = strstr(header, " symlink.target=\"");
		if (symlink)
			len += tomoyo_truncate(symlink + 1) + 1;
	}
	buffer = kmalloc(len, GFP_NOFS);
	if (!buffer)
		return;
	snprintf(buffer, len - 1, "%s", cp);
	if (realpath)
		tomoyo_addprintf(buffer, len, " exec.%s", realpath);
	if (argv0)
		tomoyo_addprintf(buffer, len, " exec.argv[0]=%s", argv0);
	if (symlink)
		tomoyo_addprintf(buffer, len, "%s", symlink);
	tomoyo_normalize_line(buffer);
	if (!tomoyo_write_domain2(domain->ns, &domain->acl_info_list, buffer,
				  false))
		tomoyo_update_stat(TOMOYO_STAT_POLICY_UPDATES);
	kfree(buffer);
}