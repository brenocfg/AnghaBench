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
typedef  enum omap_rfbi_te_mode { ____Placeholder_omap_rfbi_te_mode } omap_rfbi_te_mode ;
struct TYPE_2__ {int te_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*,int,int,int,int,int) ; 
 int EDOM ; 
 int EINVAL ; 
 int OMAP_DSS_RFBI_TE_MODE_2 ; 
 int /*<<< orphan*/  RFBI_CONFIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFBI_HSYNC_WIDTH ; 
 int /*<<< orphan*/  RFBI_VSYNC_WIDTH ; 
 int ps_to_rfbi_ticks (unsigned int,int) ; 
 TYPE_1__ rfbi ; 
 int rfbi_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfbi_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rfbi_setup_te(enum omap_rfbi_te_mode mode,
			     unsigned hs_pulse_time, unsigned vs_pulse_time,
			     int hs_pol_inv, int vs_pol_inv, int extif_div)
{
	int hs, vs;
	int min;
	u32 l;

	hs = ps_to_rfbi_ticks(hs_pulse_time, 1);
	vs = ps_to_rfbi_ticks(vs_pulse_time, 1);
	if (hs < 2)
		return -EDOM;
	if (mode == OMAP_DSS_RFBI_TE_MODE_2)
		min = 2;
	else /* OMAP_DSS_RFBI_TE_MODE_1 */
		min = 4;
	if (vs < min)
		return -EDOM;
	if (vs == hs)
		return -EINVAL;
	rfbi.te_mode = mode;
	DSSDBG("setup_te: mode %d hs %d vs %d hs_inv %d vs_inv %d\n",
		mode, hs, vs, hs_pol_inv, vs_pol_inv);

	rfbi_write_reg(RFBI_HSYNC_WIDTH, hs);
	rfbi_write_reg(RFBI_VSYNC_WIDTH, vs);

	l = rfbi_read_reg(RFBI_CONFIG(0));
	if (hs_pol_inv)
		l &= ~(1 << 21);
	else
		l |= 1 << 21;
	if (vs_pol_inv)
		l &= ~(1 << 20);
	else
		l |= 1 << 20;

	return 0;
}