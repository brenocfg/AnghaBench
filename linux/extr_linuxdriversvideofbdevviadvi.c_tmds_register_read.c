#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {TYPE_2__* chip_info; } ;
struct TYPE_4__ {scalar_t__ tmds_chip_slave_addr; int /*<<< orphan*/  i2c_port; } ;
struct TYPE_5__ {TYPE_1__ tmds_chip_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  viafb_i2c_readbyte (int /*<<< orphan*/ ,int,int,int*) ; 
 TYPE_3__* viaparinfo ; 

__attribute__((used)) static int tmds_register_read(int index)
{
	u8 data;

	viafb_i2c_readbyte(viaparinfo->chip_info->tmds_chip_info.i2c_port,
			   (u8) viaparinfo->chip_info->tmds_chip_info.tmds_chip_slave_addr,
			   (u8) index, &data);
	return data;
}