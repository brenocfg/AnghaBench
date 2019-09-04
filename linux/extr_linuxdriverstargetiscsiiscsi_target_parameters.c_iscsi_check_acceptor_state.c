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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct iscsi_param {char* name; char* value; } ;
struct iscsi_conn {int /*<<< orphan*/  param_list; TYPE_1__* conn_ops; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {unsigned long long MaxRecvDataSegmentLength; } ;

/* Variables and functions */
 char* DEFAULTTIME2RETAIN ; 
 char* DEFAULTTIME2WAIT ; 
 char* ERRORRECOVERYLEVEL ; 
 char* FIRSTBURSTLENGTH ; 
 scalar_t__ IS_PHASE_DECLARATIVE (struct iscsi_param*) ; 
 scalar_t__ IS_PSTATE_ACCEPTOR (struct iscsi_param*) ; 
 scalar_t__ IS_PSTATE_REJECT (struct iscsi_param*) ; 
 scalar_t__ IS_TYPE_BOOL_AND (struct iscsi_param*) ; 
 scalar_t__ IS_TYPE_BOOL_OR (struct iscsi_param*) ; 
 scalar_t__ IS_TYPE_NUMBER (struct iscsi_param*) ; 
 scalar_t__ IS_TYPE_VALUE_LIST (struct iscsi_param*) ; 
 char* MAXBURSTLENGTH ; 
 char* MAXCONNECTIONS ; 
 char* MAXOUTSTANDINGR2T ; 
 char* MAXRECVDATASEGMENTLENGTH ; 
 int /*<<< orphan*/  MAXXMITDATASEGMENTLENGTH ; 
 char* NO ; 
 int /*<<< orphan*/  SET_PSTATE_REPLY_OPTIONAL (struct iscsi_param*) ; 
 char* YES ; 
 char* iscsi_check_valuelist_for_support (struct iscsi_param*,char*) ; 
 struct iscsi_param* iscsi_find_param_from_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iscsi_update_param_value (struct iscsi_param*,char*) ; 
 int kstrtoull (char*,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,char*,...) ; 
 scalar_t__ simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int iscsi_check_acceptor_state(struct iscsi_param *param, char *value,
				struct iscsi_conn *conn)
{
	u8 acceptor_boolean_value = 0, proposer_boolean_value = 0;
	char *negotiated_value = NULL;

	if (IS_PSTATE_ACCEPTOR(param)) {
		pr_err("Received key \"%s\" twice, protocol error.\n",
				param->name);
		return -1;
	}

	if (IS_PSTATE_REJECT(param))
		return 0;

	if (IS_TYPE_BOOL_AND(param)) {
		if (!strcmp(value, YES))
			proposer_boolean_value = 1;
		if (!strcmp(param->value, YES))
			acceptor_boolean_value = 1;
		if (acceptor_boolean_value && proposer_boolean_value)
			do {} while (0);
		else {
			if (iscsi_update_param_value(param, NO) < 0)
				return -1;
			if (!proposer_boolean_value)
				SET_PSTATE_REPLY_OPTIONAL(param);
		}
	} else if (IS_TYPE_BOOL_OR(param)) {
		if (!strcmp(value, YES))
			proposer_boolean_value = 1;
		if (!strcmp(param->value, YES))
			acceptor_boolean_value = 1;
		if (acceptor_boolean_value || proposer_boolean_value) {
			if (iscsi_update_param_value(param, YES) < 0)
				return -1;
			if (proposer_boolean_value)
				SET_PSTATE_REPLY_OPTIONAL(param);
		}
	} else if (IS_TYPE_NUMBER(param)) {
		char *tmpptr, buf[11];
		u32 acceptor_value = simple_strtoul(param->value, &tmpptr, 0);
		u32 proposer_value = simple_strtoul(value, &tmpptr, 0);

		memset(buf, 0, sizeof(buf));

		if (!strcmp(param->name, MAXCONNECTIONS) ||
		    !strcmp(param->name, MAXBURSTLENGTH) ||
		    !strcmp(param->name, FIRSTBURSTLENGTH) ||
		    !strcmp(param->name, MAXOUTSTANDINGR2T) ||
		    !strcmp(param->name, DEFAULTTIME2RETAIN) ||
		    !strcmp(param->name, ERRORRECOVERYLEVEL)) {
			if (proposer_value > acceptor_value) {
				sprintf(buf, "%u", acceptor_value);
				if (iscsi_update_param_value(param,
						&buf[0]) < 0)
					return -1;
			} else {
				if (iscsi_update_param_value(param, value) < 0)
					return -1;
			}
		} else if (!strcmp(param->name, DEFAULTTIME2WAIT)) {
			if (acceptor_value > proposer_value) {
				sprintf(buf, "%u", acceptor_value);
				if (iscsi_update_param_value(param,
						&buf[0]) < 0)
					return -1;
			} else {
				if (iscsi_update_param_value(param, value) < 0)
					return -1;
			}
		} else {
			if (iscsi_update_param_value(param, value) < 0)
				return -1;
		}

		if (!strcmp(param->name, MAXRECVDATASEGMENTLENGTH)) {
			struct iscsi_param *param_mxdsl;
			unsigned long long tmp;
			int rc;

			rc = kstrtoull(param->value, 0, &tmp);
			if (rc < 0)
				return -1;

			conn->conn_ops->MaxRecvDataSegmentLength = tmp;
			pr_debug("Saving op->MaxRecvDataSegmentLength from"
				" original initiator received value: %u\n",
				conn->conn_ops->MaxRecvDataSegmentLength);

			param_mxdsl = iscsi_find_param_from_key(
						MAXXMITDATASEGMENTLENGTH,
						conn->param_list);
			if (!param_mxdsl)
				return -1;

			rc = iscsi_update_param_value(param,
						param_mxdsl->value);
			if (rc < 0)
				return -1;

			pr_debug("Updated %s to target MXDSL value: %s\n",
					param->name, param->value);
		}
	} else if (IS_TYPE_VALUE_LIST(param)) {
		negotiated_value = iscsi_check_valuelist_for_support(
					param, value);
		if (!negotiated_value) {
			pr_err("Proposer's value list \"%s\" contains"
				" no valid values from Acceptor's value list"
				" \"%s\".\n", value, param->value);
			return -1;
		}
		if (iscsi_update_param_value(param, negotiated_value) < 0)
			return -1;
	} else if (IS_PHASE_DECLARATIVE(param)) {
		if (iscsi_update_param_value(param, value) < 0)
			return -1;
		SET_PSTATE_REPLY_OPTIONAL(param);
	}

	return 0;
}