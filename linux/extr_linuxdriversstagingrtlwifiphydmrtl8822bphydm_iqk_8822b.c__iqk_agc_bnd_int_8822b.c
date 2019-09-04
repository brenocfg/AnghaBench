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
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  odm_write_4byte (struct phy_dm_struct*,int,int) ; 

__attribute__((used)) static void _iqk_agc_bnd_int_8822b(struct phy_dm_struct *dm)
{
	/*initialize RX AGC bnd, it must do after bbreset*/
	odm_write_4byte(dm, 0x1b00, 0xf8000008);
	odm_write_4byte(dm, 0x1b00, 0xf80a7008);
	odm_write_4byte(dm, 0x1b00, 0xf8015008);
	odm_write_4byte(dm, 0x1b00, 0xf8000008);
}