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
struct iscsi_param {int /*<<< orphan*/  name; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRSTBURSTLENGTH ; 
 int /*<<< orphan*/  IMMEDIATEDATA ; 
 scalar_t__ IS_PHASE_DECLARATIVE (struct iscsi_param*) ; 
 scalar_t__ IS_TYPE_BOOL_AND (struct iscsi_param*) ; 
 scalar_t__ IS_TYPE_BOOL_OR (struct iscsi_param*) ; 
 scalar_t__ IS_TYPE_NUMBER (struct iscsi_param*) ; 
 int /*<<< orphan*/  MAXCONNECTIONS ; 
 int /*<<< orphan*/  MAXRECVDATASEGMENTLENGTH ; 
 int /*<<< orphan*/  NO ; 
 int /*<<< orphan*/  SET_PSTATE_REPLY_OPTIONAL (struct iscsi_param*) ; 
 int /*<<< orphan*/  YES ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iscsi_check_proposer_for_optional_reply(struct iscsi_param *param,
						    bool keys_workaround)
{
	if (IS_TYPE_BOOL_AND(param)) {
		if (!strcmp(param->value, NO))
			SET_PSTATE_REPLY_OPTIONAL(param);
	} else if (IS_TYPE_BOOL_OR(param)) {
		if (!strcmp(param->value, YES))
			SET_PSTATE_REPLY_OPTIONAL(param);

		if (keys_workaround) {
			/*
			 * Required for gPXE iSCSI boot client
			 */
			if (!strcmp(param->name, IMMEDIATEDATA))
				SET_PSTATE_REPLY_OPTIONAL(param);
		}
	} else if (IS_TYPE_NUMBER(param)) {
		if (!strcmp(param->name, MAXRECVDATASEGMENTLENGTH))
			SET_PSTATE_REPLY_OPTIONAL(param);

		if (keys_workaround) {
			/*
			 * Required for Mellanox Flexboot PXE boot ROM
			 */
			if (!strcmp(param->name, FIRSTBURSTLENGTH))
				SET_PSTATE_REPLY_OPTIONAL(param);

			/*
			 * Required for gPXE iSCSI boot client
			 */
			if (!strcmp(param->name, MAXCONNECTIONS))
				SET_PSTATE_REPLY_OPTIONAL(param);
		}
	} else if (IS_PHASE_DECLARATIVE(param))
		SET_PSTATE_REPLY_OPTIONAL(param);
}