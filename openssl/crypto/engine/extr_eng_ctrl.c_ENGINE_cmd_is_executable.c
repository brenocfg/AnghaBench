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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int ENGINE_CMD_FLAG_NO_INPUT ; 
 int ENGINE_CMD_FLAG_NUMERIC ; 
 int ENGINE_CMD_FLAG_STRING ; 
 int /*<<< orphan*/  ENGINE_CTRL_GET_CMD_FLAGS ; 
 int /*<<< orphan*/  ENGINE_F_ENGINE_CMD_IS_EXECUTABLE ; 
 int /*<<< orphan*/  ENGINE_R_INVALID_CMD_NUMBER ; 
 int ENGINE_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINEerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ENGINE_cmd_is_executable(ENGINE *e, int cmd)
{
    int flags;
    if ((flags =
         ENGINE_ctrl(e, ENGINE_CTRL_GET_CMD_FLAGS, cmd, NULL, NULL)) < 0) {
        ENGINEerr(ENGINE_F_ENGINE_CMD_IS_EXECUTABLE,
                  ENGINE_R_INVALID_CMD_NUMBER);
        return 0;
    }
    if (!(flags & ENGINE_CMD_FLAG_NO_INPUT) &&
        !(flags & ENGINE_CMD_FLAG_NUMERIC) &&
        !(flags & ENGINE_CMD_FLAG_STRING))
        return 0;
    return 1;
}