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
typedef  int u16 ;
struct zd_ioreq32 {int value; int /*<<< orphan*/  addr; } ;
struct zd_chip {int dummy; } ;
struct aw_pt_bi {int beacon_interval; int pre_tbtt; int atim_wnd_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct zd_ioreq32*) ; 
 int /*<<< orphan*/  CR_ATIM_WND_PERIOD ; 
 int /*<<< orphan*/  CR_BCN_INTERVAL ; 
 int /*<<< orphan*/  CR_PRE_TBTT ; 
 int zd_iowrite32a_locked (struct zd_chip*,struct zd_ioreq32*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_aw_pt_bi(struct zd_chip *chip, struct aw_pt_bi *s)
{
	struct zd_ioreq32 reqs[3];
	u16 b_interval = s->beacon_interval & 0xffff;

	if (b_interval <= 5)
		b_interval = 5;
	if (s->pre_tbtt < 4 || s->pre_tbtt >= b_interval)
		s->pre_tbtt = b_interval - 1;
	if (s->atim_wnd_period >= s->pre_tbtt)
		s->atim_wnd_period = s->pre_tbtt - 1;

	reqs[0].addr = CR_ATIM_WND_PERIOD;
	reqs[0].value = s->atim_wnd_period;
	reqs[1].addr = CR_PRE_TBTT;
	reqs[1].value = s->pre_tbtt;
	reqs[2].addr = CR_BCN_INTERVAL;
	reqs[2].value = (s->beacon_interval & ~0xffff) | b_interval;

	return zd_iowrite32a_locked(chip, reqs, ARRAY_SIZE(reqs));
}