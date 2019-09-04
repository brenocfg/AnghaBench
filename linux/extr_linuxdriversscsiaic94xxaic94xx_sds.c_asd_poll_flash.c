#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  bar; } ;
struct TYPE_4__ {TYPE_1__ flash; } ;
struct asd_ha_struct {TYPE_2__ hw_prof; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  asd_read_reg_byte (struct asd_ha_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int asd_poll_flash(struct asd_ha_struct *asd_ha)
{
	int c;
	u8 d;

	for (c = 5000; c > 0; c--) {
		d  = asd_read_reg_byte(asd_ha, asd_ha->hw_prof.flash.bar);
		d ^= asd_read_reg_byte(asd_ha, asd_ha->hw_prof.flash.bar);
		if (!d)
			return 0;
		udelay(5);
	}
	return -ENOENT;
}