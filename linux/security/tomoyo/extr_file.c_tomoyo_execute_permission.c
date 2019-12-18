#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  operation; struct tomoyo_path_info const* filename; } ;
struct TYPE_9__ {TYPE_2__ path; } ;
struct tomoyo_request_info {scalar_t__ mode; TYPE_6__* matched_acl; TYPE_4__* ee; TYPE_3__ param; int /*<<< orphan*/  param_type; int /*<<< orphan*/  type; int /*<<< orphan*/  profile; TYPE_1__* domain; } ;
struct tomoyo_path_info {int dummy; } ;
struct TYPE_12__ {TYPE_5__* cond; } ;
struct TYPE_11__ {int /*<<< orphan*/ * transit; } ;
struct TYPE_10__ {int /*<<< orphan*/ * transition; } ;
struct TYPE_7__ {int /*<<< orphan*/  ns; } ;

/* Variables and functions */
 scalar_t__ TOMOYO_CONFIG_DISABLED ; 
 int /*<<< orphan*/  TOMOYO_MAC_FILE_EXECUTE ; 
 int /*<<< orphan*/  TOMOYO_TYPE_EXECUTE ; 
 int /*<<< orphan*/  TOMOYO_TYPE_PATH_ACL ; 
 int tomoyo_audit_path_log (struct tomoyo_request_info*) ; 
 int /*<<< orphan*/  tomoyo_check_acl (struct tomoyo_request_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tomoyo_check_path_acl ; 
 scalar_t__ tomoyo_get_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tomoyo_execute_permission(struct tomoyo_request_info *r,
			      const struct tomoyo_path_info *filename)
{
	/*
	 * Unlike other permission checks, this check is done regardless of
	 * profile mode settings in order to check for domain transition
	 * preference.
	 */
	r->type = TOMOYO_MAC_FILE_EXECUTE;
	r->mode = tomoyo_get_mode(r->domain->ns, r->profile, r->type);
	r->param_type = TOMOYO_TYPE_PATH_ACL;
	r->param.path.filename = filename;
	r->param.path.operation = TOMOYO_TYPE_EXECUTE;
	tomoyo_check_acl(r, tomoyo_check_path_acl);
	r->ee->transition = r->matched_acl && r->matched_acl->cond ?
		r->matched_acl->cond->transit : NULL;
	if (r->mode != TOMOYO_CONFIG_DISABLED)
		return tomoyo_audit_path_log(r);
	return 0;
}