#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct tomoyo_request_info {TYPE_5__* ee; TYPE_4__* obj; TYPE_2__* domain; } ;
struct linux_binprm {int argc; int envc; struct file* file; } ;
struct file {int /*<<< orphan*/  f_path; } ;
struct TYPE_10__ {struct linux_binprm* bprm; int /*<<< orphan*/  dump; } ;
struct TYPE_9__ {TYPE_3__* symlink_target; } ;
struct TYPE_8__ {char* name; } ;
struct TYPE_7__ {TYPE_1__* domainname; } ;
struct TYPE_6__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char const*,...) ; 
 scalar_t__ strlen (char const*) ; 
 char* tomoyo_print_bprm (struct linux_binprm*,int /*<<< orphan*/ *) ; 
 char* tomoyo_print_header (struct tomoyo_request_info*) ; 
 char* tomoyo_realpath_from_path (int /*<<< orphan*/ *) ; 
 int tomoyo_round2 (int) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

char *tomoyo_init_log(struct tomoyo_request_info *r, int len, const char *fmt,
		      va_list args)
{
	char *buf = NULL;
	char *bprm_info = NULL;
	const char *header = NULL;
	char *realpath = NULL;
	const char *symlink = NULL;
	int pos;
	const char *domainname = r->domain->domainname->name;

	header = tomoyo_print_header(r);
	if (!header)
		return NULL;
	/* +10 is for '\n' etc. and '\0'. */
	len += strlen(domainname) + strlen(header) + 10;
	if (r->ee) {
		struct file *file = r->ee->bprm->file;

		realpath = tomoyo_realpath_from_path(&file->f_path);
		bprm_info = tomoyo_print_bprm(r->ee->bprm, &r->ee->dump);
		if (!realpath || !bprm_info)
			goto out;
		/* +80 is for " exec={ realpath=\"%s\" argc=%d envc=%d %s }" */
		len += strlen(realpath) + 80 + strlen(bprm_info);
	} else if (r->obj && r->obj->symlink_target) {
		symlink = r->obj->symlink_target->name;
		/* +18 is for " symlink.target=\"%s\"" */
		len += 18 + strlen(symlink);
	}
	len = tomoyo_round2(len);
	buf = kzalloc(len, GFP_NOFS);
	if (!buf)
		goto out;
	len--;
	pos = snprintf(buf, len, "%s", header);
	if (realpath) {
		struct linux_binprm *bprm = r->ee->bprm;

		pos += snprintf(buf + pos, len - pos,
				" exec={ realpath=\"%s\" argc=%d envc=%d %s }",
				realpath, bprm->argc, bprm->envc, bprm_info);
	} else if (symlink)
		pos += snprintf(buf + pos, len - pos, " symlink.target=\"%s\"",
				symlink);
	pos += snprintf(buf + pos, len - pos, "\n%s\n", domainname);
	vsnprintf(buf + pos, len - pos, fmt, args);
out:
	kfree(realpath);
	kfree(bprm_info);
	kfree(header);
	return buf;
}