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
struct TYPE_2__ {int te_mode; int te_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*,int,unsigned int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  RFBI_CONFIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFBI_LINE_NUMBER ; 
 TYPE_1__ rfbi ; 
 int rfbi_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfbi_write_reg (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int rfbi_enable_te(bool enable, unsigned line)
{
	u32 l;

	DSSDBG("te %d line %d mode %d\n", enable, line, rfbi.te_mode);
	if (line > (1 << 11) - 1)
		return -EINVAL;

	l = rfbi_read_reg(RFBI_CONFIG(0));
	l &= ~(0x3 << 2);
	if (enable) {
		rfbi.te_enabled = 1;
		l |= rfbi.te_mode << 2;
	} else
		rfbi.te_enabled = 0;
	rfbi_write_reg(RFBI_CONFIG(0), l);
	rfbi_write_reg(RFBI_LINE_NUMBER, line);

	return 0;
}