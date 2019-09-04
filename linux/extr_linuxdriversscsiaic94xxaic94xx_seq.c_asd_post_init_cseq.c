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
struct asd_ha_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARP2INTCTL ; 
 int /*<<< orphan*/  CMnINT (int) ; 
 int /*<<< orphan*/  CMnRSPMBX (int) ; 
 int /*<<< orphan*/  RSTINTCTL ; 
 int /*<<< orphan*/  asd_read_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_write_reg_byte (struct asd_ha_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_write_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void asd_post_init_cseq(struct asd_ha_struct *asd_ha)
{
	int i;

	for (i = 0; i < 8; i++)
		asd_write_reg_dword(asd_ha, CMnINT(i), 0xFFFFFFFF);
	for (i = 0; i < 8; i++)
		asd_read_reg_dword(asd_ha, CMnRSPMBX(i));
	/* Reset the external interrupt arbiter. */
	asd_write_reg_byte(asd_ha, CARP2INTCTL, RSTINTCTL);
}