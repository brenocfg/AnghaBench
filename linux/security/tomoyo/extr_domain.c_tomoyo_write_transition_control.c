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
typedef  scalar_t__ u8 ;
struct tomoyo_transition_control {scalar_t__ const type; int is_last_name; void* program; void* domainname; int /*<<< orphan*/  head; } ;
struct tomoyo_acl_param {char* data; TYPE_1__* ns; int /*<<< orphan*/ * list; scalar_t__ is_delete; } ;
typedef  int /*<<< orphan*/  e ;
struct TYPE_2__ {int /*<<< orphan*/ * policy_list; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 size_t TOMOYO_ID_TRANSITION_CONTROL ; 
 scalar_t__ const TOMOYO_TRANSITION_CONTROL_KEEP ; 
 scalar_t__ const TOMOYO_TRANSITION_CONTROL_NO_KEEP ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  tomoyo_correct_domain (char*) ; 
 int /*<<< orphan*/  tomoyo_correct_path (char*) ; 
 void* tomoyo_get_name (char*) ; 
 int /*<<< orphan*/  tomoyo_put_name (void*) ; 
 int /*<<< orphan*/  tomoyo_same_transition_control ; 
 int tomoyo_update_policy (int /*<<< orphan*/ *,int,struct tomoyo_acl_param*,int /*<<< orphan*/ ) ; 

int tomoyo_write_transition_control(struct tomoyo_acl_param *param,
				    const u8 type)
{
	struct tomoyo_transition_control e = { .type = type };
	int error = param->is_delete ? -ENOENT : -ENOMEM;
	char *program = param->data;
	char *domainname = strstr(program, " from ");

	if (domainname) {
		*domainname = '\0';
		domainname += 6;
	} else if (type == TOMOYO_TRANSITION_CONTROL_NO_KEEP ||
		   type == TOMOYO_TRANSITION_CONTROL_KEEP) {
		domainname = program;
		program = NULL;
	}
	if (program && strcmp(program, "any")) {
		if (!tomoyo_correct_path(program))
			return -EINVAL;
		e.program = tomoyo_get_name(program);
		if (!e.program)
			goto out;
	}
	if (domainname && strcmp(domainname, "any")) {
		if (!tomoyo_correct_domain(domainname)) {
			if (!tomoyo_correct_path(domainname))
				goto out;
			e.is_last_name = true;
		}
		e.domainname = tomoyo_get_name(domainname);
		if (!e.domainname)
			goto out;
	}
	param->list = &param->ns->policy_list[TOMOYO_ID_TRANSITION_CONTROL];
	error = tomoyo_update_policy(&e.head, sizeof(e), param,
				     tomoyo_same_transition_control);
out:
	tomoyo_put_name(e.domainname);
	tomoyo_put_name(e.program);
	return error;
}