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
typedef  size_t ftp_cmd_index_t ;
struct TYPE_2__ {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 size_t E_FTP_CMD_NOT_SUPPORTED ; 
 size_t E_FTP_NUM_FTP_CMDS ; 
 int FTP_CMD_SIZE_MAX ; 
 TYPE_1__* ftp_cmd_table ; 
 int /*<<< orphan*/  ftp_pop_param (char**,char*) ; 
 int /*<<< orphan*/  stoupper (char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ftp_cmd_index_t ftp_pop_command (char **str) {
    char _cmd[FTP_CMD_SIZE_MAX];
    ftp_pop_param (str, _cmd);
    stoupper (_cmd);
    for (ftp_cmd_index_t i = 0; i < E_FTP_NUM_FTP_CMDS; i++) {
        if (!strcmp (_cmd, ftp_cmd_table[i].cmd)) {
            // move one step further to skip the space
            (*str)++;
            return i;
        }
    }
    return E_FTP_CMD_NOT_SUPPORTED;
}