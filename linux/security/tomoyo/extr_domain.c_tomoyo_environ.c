#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tomoyo_request_info {scalar_t__ mode; int /*<<< orphan*/  profile; TYPE_1__* domain; int /*<<< orphan*/  type; } ;
struct tomoyo_page_dump {unsigned char* data; } ;
struct tomoyo_execve {struct tomoyo_request_info r; struct linux_binprm* bprm; } ;
struct linux_binprm {unsigned long p; int argc; int envc; } ;
struct TYPE_2__ {int /*<<< orphan*/  ns; int /*<<< orphan*/  profile; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 unsigned long PAGE_SIZE ; 
 scalar_t__ TOMOYO_CONFIG_ENFORCING ; 
 int TOMOYO_EXEC_TMPSIZE ; 
 int /*<<< orphan*/  TOMOYO_MAC_ENVIRON ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tomoyo_dump_page (struct linux_binprm*,unsigned long,struct tomoyo_page_dump*) ; 
 scalar_t__ tomoyo_env_perm (struct tomoyo_request_info*,char*) ; 
 scalar_t__ tomoyo_get_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tomoyo_environ(struct tomoyo_execve *ee)
{
	struct tomoyo_request_info *r = &ee->r;
	struct linux_binprm *bprm = ee->bprm;
	/* env_page.data is allocated by tomoyo_dump_page(). */
	struct tomoyo_page_dump env_page = { };
	char *arg_ptr; /* Size is TOMOYO_EXEC_TMPSIZE bytes */
	int arg_len = 0;
	unsigned long pos = bprm->p;
	int offset = pos % PAGE_SIZE;
	int argv_count = bprm->argc;
	int envp_count = bprm->envc;
	int error = -ENOMEM;

	ee->r.type = TOMOYO_MAC_ENVIRON;
	ee->r.profile = r->domain->profile;
	ee->r.mode = tomoyo_get_mode(r->domain->ns, ee->r.profile,
				     TOMOYO_MAC_ENVIRON);
	if (!r->mode || !envp_count)
		return 0;
	arg_ptr = kzalloc(TOMOYO_EXEC_TMPSIZE, GFP_NOFS);
	if (!arg_ptr)
		goto out;
	while (error == -ENOMEM) {
		if (!tomoyo_dump_page(bprm, pos, &env_page))
			goto out;
		pos += PAGE_SIZE - offset;
		/* Read. */
		while (argv_count && offset < PAGE_SIZE) {
			if (!env_page.data[offset++])
				argv_count--;
		}
		if (argv_count) {
			offset = 0;
			continue;
		}
		while (offset < PAGE_SIZE) {
			const unsigned char c = env_page.data[offset++];

			if (c && arg_len < TOMOYO_EXEC_TMPSIZE - 10) {
				if (c == '=') {
					arg_ptr[arg_len++] = '\0';
				} else if (c == '\\') {
					arg_ptr[arg_len++] = '\\';
					arg_ptr[arg_len++] = '\\';
				} else if (c > ' ' && c < 127) {
					arg_ptr[arg_len++] = c;
				} else {
					arg_ptr[arg_len++] = '\\';
					arg_ptr[arg_len++] = (c >> 6) + '0';
					arg_ptr[arg_len++]
						= ((c >> 3) & 7) + '0';
					arg_ptr[arg_len++] = (c & 7) + '0';
				}
			} else {
				arg_ptr[arg_len] = '\0';
			}
			if (c)
				continue;
			if (tomoyo_env_perm(r, arg_ptr)) {
				error = -EPERM;
				break;
			}
			if (!--envp_count) {
				error = 0;
				break;
			}
			arg_len = 0;
		}
		offset = 0;
	}
out:
	if (r->mode != TOMOYO_CONFIG_ENFORCING)
		error = 0;
	kfree(env_page.data);
	kfree(arg_ptr);
	return error;
}