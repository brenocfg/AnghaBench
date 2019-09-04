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
typedef  int u32 ;
struct asd_ha_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DPRINTK (char*) ; 
 int /*<<< orphan*/  CARP2CTL ; 
 int EPAUSE ; 
 int PAUSED ; 
 int /*<<< orphan*/  PAUSE_DELAY ; 
 int PAUSE_TRIES ; 
 int asd_read_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_write_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asd_unpause_cseq(struct asd_ha_struct *asd_ha)
{
	u32	arp2ctl;
	int	count = PAUSE_TRIES;

	arp2ctl = asd_read_reg_dword(asd_ha, CARP2CTL);
	if (!(arp2ctl & PAUSED))
		return 0;

	asd_write_reg_dword(asd_ha, CARP2CTL, arp2ctl & ~EPAUSE);
	do {
		arp2ctl = asd_read_reg_dword(asd_ha, CARP2CTL);
		if (!(arp2ctl & PAUSED))
			return 0;
		udelay(PAUSE_DELAY);
	} while (--count > 0);

	ASD_DPRINTK("couldn't unpause the CSEQ\n");
	return -1;
}