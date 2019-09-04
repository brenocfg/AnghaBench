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
typedef  int /*<<< orphan*/  const u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct dc_rtc {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
#define  CMD_NOP 130 
#define  CMD_RESET 129 
#define  CMD_WRITE 128 
 scalar_t__ DC_RTC_REFERENCE ; 
 int dc_rtc_cmds (struct dc_rtc*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int dc_rtc_write(struct dc_rtc *rtc, u32 val)
{
	static const u8 write_cmds[] = {CMD_WRITE, CMD_NOP, CMD_RESET, CMD_NOP};

	writel_relaxed(val, rtc->regs + DC_RTC_REFERENCE);
	return dc_rtc_cmds(rtc, write_cmds, ARRAY_SIZE(write_cmds));
}