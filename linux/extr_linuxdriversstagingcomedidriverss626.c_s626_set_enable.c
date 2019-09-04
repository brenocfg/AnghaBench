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
typedef  int /*<<< orphan*/  u16 ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int S626_CRBMSK_CLKENAB_A ; 
 unsigned int S626_CRBMSK_CLKENAB_B ; 
 unsigned int S626_CRBMSK_INTCTRL ; 
 int /*<<< orphan*/  S626_LP_CRB (unsigned int) ; 
 unsigned int S626_SET_CRB_CLKENAB_A (int /*<<< orphan*/ ) ; 
 unsigned int S626_SET_CRB_CLKENAB_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_debi_replace (struct comedi_device*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void s626_set_enable(struct comedi_device *dev,
			    unsigned int chan, u16 enab)
{
	unsigned int mask = S626_CRBMSK_INTCTRL;
	unsigned int set;

	if (chan < 3) {
		mask |= S626_CRBMSK_CLKENAB_A;
		set = S626_SET_CRB_CLKENAB_A(enab);
	} else {
		mask |= S626_CRBMSK_CLKENAB_B;
		set = S626_SET_CRB_CLKENAB_B(enab);
	}
	s626_debi_replace(dev, S626_LP_CRB(chan), ~mask, set);
}