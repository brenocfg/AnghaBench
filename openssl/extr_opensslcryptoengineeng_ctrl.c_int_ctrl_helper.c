#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__ const* cmd_defns; } ;
struct TYPE_7__ {int cmd_num; int cmd_flags; int /*<<< orphan*/ * cmd_desc; int /*<<< orphan*/ * cmd_name; } ;
typedef  TYPE_1__ const ENGINE_CMD_DEFN ;
typedef  TYPE_2__ ENGINE ;

/* Variables and functions */
#define  ENGINE_CTRL_GET_CMD_FLAGS 133 
 int ENGINE_CTRL_GET_CMD_FROM_NAME ; 
#define  ENGINE_CTRL_GET_DESC_FROM_CMD 132 
#define  ENGINE_CTRL_GET_DESC_LEN_FROM_CMD 131 
 int ENGINE_CTRL_GET_FIRST_CMD_TYPE ; 
#define  ENGINE_CTRL_GET_NAME_FROM_CMD 130 
#define  ENGINE_CTRL_GET_NAME_LEN_FROM_CMD 129 
#define  ENGINE_CTRL_GET_NEXT_CMD_TYPE 128 
 int /*<<< orphan*/  ENGINE_F_INT_CTRL_HELPER ; 
 int /*<<< orphan*/  ENGINE_R_INTERNAL_LIST_ERROR ; 
 int /*<<< orphan*/  ENGINE_R_INVALID_CMD_NAME ; 
 int /*<<< orphan*/  ENGINE_R_INVALID_CMD_NUMBER ; 
 int /*<<< orphan*/  ENGINEerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int int_ctrl_cmd_by_name (TYPE_1__ const*,char*) ; 
 int int_ctrl_cmd_by_num (TYPE_1__ const*,unsigned int) ; 
 scalar_t__ int_ctrl_cmd_is_null (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * int_no_description ; 
 int /*<<< orphan*/ * strcpy (char*,int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int int_ctrl_helper(ENGINE *e, int cmd, long i, void *p,
                           void (*f) (void))
{
    int idx;
    char *s = (char *)p;
    const ENGINE_CMD_DEFN *cdp;

    /* Take care of the easy one first (eg. it requires no searches) */
    if (cmd == ENGINE_CTRL_GET_FIRST_CMD_TYPE) {
        if ((e->cmd_defns == NULL) || int_ctrl_cmd_is_null(e->cmd_defns))
            return 0;
        return e->cmd_defns->cmd_num;
    }
    /* One or two commands require that "p" be a valid string buffer */
    if ((cmd == ENGINE_CTRL_GET_CMD_FROM_NAME) ||
        (cmd == ENGINE_CTRL_GET_NAME_FROM_CMD) ||
        (cmd == ENGINE_CTRL_GET_DESC_FROM_CMD)) {
        if (s == NULL) {
            ENGINEerr(ENGINE_F_INT_CTRL_HELPER, ERR_R_PASSED_NULL_PARAMETER);
            return -1;
        }
    }
    /* Now handle cmd_name -> cmd_num conversion */
    if (cmd == ENGINE_CTRL_GET_CMD_FROM_NAME) {
        if ((e->cmd_defns == NULL)
            || ((idx = int_ctrl_cmd_by_name(e->cmd_defns, s)) < 0)) {
            ENGINEerr(ENGINE_F_INT_CTRL_HELPER, ENGINE_R_INVALID_CMD_NAME);
            return -1;
        }
        return e->cmd_defns[idx].cmd_num;
    }
    /*
     * For the rest of the commands, the 'long' argument must specify a valid
     * command number - so we need to conduct a search.
     */
    if ((e->cmd_defns == NULL)
        || ((idx = int_ctrl_cmd_by_num(e->cmd_defns, (unsigned int)i)) < 0)) {
        ENGINEerr(ENGINE_F_INT_CTRL_HELPER, ENGINE_R_INVALID_CMD_NUMBER);
        return -1;
    }
    /* Now the logic splits depending on command type */
    cdp = &e->cmd_defns[idx];
    switch (cmd) {
    case ENGINE_CTRL_GET_NEXT_CMD_TYPE:
        cdp++;
        return int_ctrl_cmd_is_null(cdp) ? 0 : cdp->cmd_num;
    case ENGINE_CTRL_GET_NAME_LEN_FROM_CMD:
        return strlen(cdp->cmd_name);
    case ENGINE_CTRL_GET_NAME_FROM_CMD:
        return strlen(strcpy(s, cdp->cmd_name));
    case ENGINE_CTRL_GET_DESC_LEN_FROM_CMD:
        return strlen(cdp->cmd_desc == NULL ? int_no_description
                                            : cdp->cmd_desc);
    case ENGINE_CTRL_GET_DESC_FROM_CMD:
        return strlen(strcpy(s, cdp->cmd_desc == NULL ? int_no_description
                                                      : cdp->cmd_desc));
    case ENGINE_CTRL_GET_CMD_FLAGS:
        return cdp->cmd_flags;
    }
    /* Shouldn't really be here ... */
    ENGINEerr(ENGINE_F_INT_CTRL_HELPER, ENGINE_R_INTERNAL_LIST_ERROR);
    return -1;
}