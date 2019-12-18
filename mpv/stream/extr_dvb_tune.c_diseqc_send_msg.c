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
struct diseqc_cmd {int wait; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/ * fe_sec_voltage_t ;
typedef  int /*<<< orphan*/ * fe_sec_tone_mode_t ;
typedef  int /*<<< orphan*/ * fe_sec_mini_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  FE_DISEQC_SEND_BURST ; 
 int /*<<< orphan*/  FE_DISEQC_SEND_MASTER_CMD ; 
 int /*<<< orphan*/  FE_SET_TONE ; 
 int /*<<< orphan*/  FE_SET_VOLTAGE ; 
 int /*<<< orphan*/ * SEC_TONE_OFF ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static int diseqc_send_msg(int fd, fe_sec_voltage_t v, struct diseqc_cmd *cmd,
                           fe_sec_tone_mode_t t, fe_sec_mini_cmd_t b)
{
    if (ioctl(fd, FE_SET_TONE, SEC_TONE_OFF) < 0)
        return -1;
    if (ioctl(fd, FE_SET_VOLTAGE, v) < 0)
        return -1;
    usleep(15 * 1000);
    if (ioctl(fd, FE_DISEQC_SEND_MASTER_CMD, &cmd->cmd) < 0)
        return -1;
    usleep(cmd->wait * 1000);
    usleep(15 * 1000);
    if (ioctl(fd, FE_DISEQC_SEND_BURST, b) < 0)
        return -1;
    usleep(15 * 1000);
    if (ioctl(fd, FE_SET_TONE, t) < 0)
        return -1;
    usleep(100000);

    return 0;
}