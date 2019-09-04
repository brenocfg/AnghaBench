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
typedef  int u32 ;
struct TYPE_2__ {int l4_khz; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*,int,...) ; 
 int /*<<< orphan*/  RFBI_CONFIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFBI_CYCLE_TIME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFBI_ONOFF_TIME (int /*<<< orphan*/ ) ; 
 TYPE_1__ rfbi ; 
 int rfbi_read_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rfbi_print_timings(void)
{
	u32 l;
	u32 time;

	l = rfbi_read_reg(RFBI_CONFIG(0));
	time = 1000000000 / rfbi.l4_khz;
	if (l & (1 << 4))
		time *= 2;

	DSSDBG("Tick time %u ps\n", time);
	l = rfbi_read_reg(RFBI_ONOFF_TIME(0));
	DSSDBG("CSONTIME %d, CSOFFTIME %d, WEONTIME %d, WEOFFTIME %d, "
		"REONTIME %d, REOFFTIME %d\n",
		l & 0x0f, (l >> 4) & 0x3f, (l >> 10) & 0x0f, (l >> 14) & 0x3f,
		(l >> 20) & 0x0f, (l >> 24) & 0x3f);

	l = rfbi_read_reg(RFBI_CYCLE_TIME(0));
	DSSDBG("WECYCLETIME %d, RECYCLETIME %d, CSPULSEWIDTH %d, "
		"ACCESSTIME %d\n",
		(l & 0x3f), (l >> 6) & 0x3f, (l >> 12) & 0x3f,
		(l >> 22) & 0x3f);
}