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

/* Variables and functions */
 int /*<<< orphan*/  REG_SFDR_CFG ; 
 int /*<<< orphan*/  qm_ccsr_out (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qm_set_sfdr_threshold(u16 th)
{
	qm_ccsr_out(REG_SFDR_CFG, th & 0x3ff);
}