#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * ctrl; } ;
typedef  TYPE_1__ ENGINE ;

/* Variables and functions */
 int ENGINE_CMD_FLAG_NO_INPUT ; 
 int ENGINE_CMD_FLAG_NUMERIC ; 
 int ENGINE_CMD_FLAG_STRING ; 
 int ENGINE_CTRL_GET_CMD_FLAGS ; 
 int ENGINE_CTRL_GET_CMD_FROM_NAME ; 
 int /*<<< orphan*/  ENGINE_F_ENGINE_CTRL_CMD_STRING ; 
 int /*<<< orphan*/  ENGINE_R_ARGUMENT_IS_NOT_A_NUMBER ; 
 int /*<<< orphan*/  ENGINE_R_CMD_NOT_EXECUTABLE ; 
 int /*<<< orphan*/  ENGINE_R_COMMAND_TAKES_INPUT ; 
 int /*<<< orphan*/  ENGINE_R_COMMAND_TAKES_NO_INPUT ; 
 int /*<<< orphan*/  ENGINE_R_INTERNAL_LIST_ERROR ; 
 int /*<<< orphan*/  ENGINE_R_INVALID_CMD_NAME ; 
 int /*<<< orphan*/  ENGINE_cmd_is_executable (TYPE_1__*,int) ; 
 int ENGINE_ctrl (TYPE_1__*,int,long,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINEerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 long strtol (char const*,char**,int) ; 

int ENGINE_ctrl_cmd_string(ENGINE *e, const char *cmd_name, const char *arg,
                           int cmd_optional)
{
    int num, flags;
    long l;
    char *ptr;

    if (e == NULL || cmd_name == NULL) {
        ENGINEerr(ENGINE_F_ENGINE_CTRL_CMD_STRING, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }
    if (e->ctrl == NULL
        || (num = ENGINE_ctrl(e, ENGINE_CTRL_GET_CMD_FROM_NAME,
                              0, (void *)cmd_name, NULL)) <= 0) {
        /*
         * If the command didn't *have* to be supported, we fake success.
         * This allows certain settings to be specified for multiple ENGINEs
         * and only require a change of ENGINE id (without having to
         * selectively apply settings). Eg. changing from a hardware device
         * back to the regular software ENGINE without editing the config
         * file, etc.
         */
        if (cmd_optional) {
            ERR_clear_error();
            return 1;
        }
        ENGINEerr(ENGINE_F_ENGINE_CTRL_CMD_STRING, ENGINE_R_INVALID_CMD_NAME);
        return 0;
    }
    if (!ENGINE_cmd_is_executable(e, num)) {
        ENGINEerr(ENGINE_F_ENGINE_CTRL_CMD_STRING,
                  ENGINE_R_CMD_NOT_EXECUTABLE);
        return 0;
    }

    flags = ENGINE_ctrl(e, ENGINE_CTRL_GET_CMD_FLAGS, num, NULL, NULL);
    if (flags < 0) {
        /*
         * Shouldn't happen, given that ENGINE_cmd_is_executable() returned
         * success.
         */
        ENGINEerr(ENGINE_F_ENGINE_CTRL_CMD_STRING,
                  ENGINE_R_INTERNAL_LIST_ERROR);
        return 0;
    }
    /*
     * If the command takes no input, there must be no input. And vice versa.
     */
    if (flags & ENGINE_CMD_FLAG_NO_INPUT) {
        if (arg != NULL) {
            ENGINEerr(ENGINE_F_ENGINE_CTRL_CMD_STRING,
                      ENGINE_R_COMMAND_TAKES_NO_INPUT);
            return 0;
        }
        /*
         * We deliberately force the result of ENGINE_ctrl() to 0 or 1 rather
         * than returning it as "return data". This is to ensure usage of
         * these commands is consistent across applications and that certain
         * applications don't understand it one way, and others another.
         */
        if (ENGINE_ctrl(e, num, 0, (void *)arg, NULL) > 0)
            return 1;
        return 0;
    }
    /* So, we require input */
    if (arg == NULL) {
        ENGINEerr(ENGINE_F_ENGINE_CTRL_CMD_STRING,
                  ENGINE_R_COMMAND_TAKES_INPUT);
        return 0;
    }
    /* If it takes string input, that's easy */
    if (flags & ENGINE_CMD_FLAG_STRING) {
        /* Same explanation as above */
        if (ENGINE_ctrl(e, num, 0, (void *)arg, NULL) > 0)
            return 1;
        return 0;
    }
    /*
     * If it doesn't take numeric either, then it is unsupported for use in a
     * config-setting situation, which is what this function is for. This
     * should never happen though, because ENGINE_cmd_is_executable() was
     * used.
     */
    if (!(flags & ENGINE_CMD_FLAG_NUMERIC)) {
        ENGINEerr(ENGINE_F_ENGINE_CTRL_CMD_STRING,
                  ENGINE_R_INTERNAL_LIST_ERROR);
        return 0;
    }
    l = strtol(arg, &ptr, 10);
    if ((arg == ptr) || (*ptr != '\0')) {
        ENGINEerr(ENGINE_F_ENGINE_CTRL_CMD_STRING,
                  ENGINE_R_ARGUMENT_IS_NOT_A_NUMBER);
        return 0;
    }
    /*
     * Force the result of the control command to 0 or 1, for the reasons
     * mentioned before.
     */
    if (ENGINE_ctrl(e, num, l, NULL, NULL) > 0)
        return 1;
    return 0;
}