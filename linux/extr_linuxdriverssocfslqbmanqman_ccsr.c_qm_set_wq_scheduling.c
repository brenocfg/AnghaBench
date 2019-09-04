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
typedef  int u8 ;
typedef  enum qm_wq_class { ____Placeholder_qm_wq_class } qm_wq_class ;

/* Variables and functions */
 int /*<<< orphan*/  REG_WQ_CS_CFG (int) ; 
 int /*<<< orphan*/  qm_ccsr_out (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qm_set_wq_scheduling(enum qm_wq_class wq_class,
				 u8 cs_elev, u8 csw2, u8 csw3, u8 csw4,
				 u8 csw5, u8 csw6, u8 csw7)
{
	qm_ccsr_out(REG_WQ_CS_CFG(wq_class), ((cs_elev & 0xff) << 24) |
		    ((csw2 & 0x7) << 20) | ((csw3 & 0x7) << 16) |
		    ((csw4 & 0x7) << 12) | ((csw5 & 0x7) << 8) |
		    ((csw6 & 0x7) << 4) | (csw7 & 0x7));
}