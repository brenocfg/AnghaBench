#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* cmd; char* arg; } ;
typedef  TYPE_1__ SSL_CONF_CMD ;

/* Variables and functions */

void conf_ssl_get_cmd(const SSL_CONF_CMD *cmd, size_t idx, char **cmdstr,
                      char **arg)
{
    *cmdstr = cmd[idx].cmd;
    *arg = cmd[idx].arg;
}