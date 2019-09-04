#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* msg; } ;
struct TYPE_5__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; } ;
struct TYPE_4__ {int member_1; TYPE_2__ member_0; } ;
struct diseqc_cmd {TYPE_3__ cmd; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_MINI_A ; 
 int /*<<< orphan*/  SEC_MINI_B ; 
 int /*<<< orphan*/  SEC_TONE_OFF ; 
 int /*<<< orphan*/  SEC_TONE_ON ; 
 int /*<<< orphan*/  SEC_VOLTAGE_13 ; 
 int /*<<< orphan*/  SEC_VOLTAGE_18 ; 
 int diseqc_send_msg (int,int /*<<< orphan*/ ,struct diseqc_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_diseqc(int secfd, int sat_no, int polv, int hi_lo)
{
    struct diseqc_cmd cmd =  { {{0xe0, 0x10, 0x38, 0xf0, 0x00, 0x00}, 4}, 0 };

    /* param: high nibble: reset bits, low nibble set bits,
     * bits are: option, position, polarizaion, band
     */
    cmd.cmd.msg[3] = 0xf0 | (((sat_no * 4) & 0x0f) | (hi_lo ? 1 : 0) | (polv ? 0 : 2));

    return diseqc_send_msg(secfd, polv ? SEC_VOLTAGE_13 : SEC_VOLTAGE_18,
                           &cmd, hi_lo ? SEC_TONE_ON : SEC_TONE_OFF,
                           ((sat_no / 4) % 2) ? SEC_MINI_B : SEC_MINI_A);
}