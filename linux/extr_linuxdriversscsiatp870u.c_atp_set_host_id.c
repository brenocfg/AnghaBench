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
struct atp_unit {int dummy; } ;

/* Variables and functions */
 int atp_readb_io (struct atp_unit*,int,int) ; 
 int /*<<< orphan*/  atp_writeb_io (struct atp_unit*,int,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void atp_set_host_id(struct atp_unit *atp, u8 c, u8 host_id)
{
	atp_writeb_io(atp, c, 0, host_id | 0x08);
	atp_writeb_io(atp, c, 0x18, 0);
	while ((atp_readb_io(atp, c, 0x1f) & 0x80) == 0)
		mdelay(1);
	atp_readb_io(atp, c, 0x17);
	atp_writeb_io(atp, c, 1, 8);
	atp_writeb_io(atp, c, 2, 0x7f);
	atp_writeb_io(atp, c, 0x11, 0x20);
}