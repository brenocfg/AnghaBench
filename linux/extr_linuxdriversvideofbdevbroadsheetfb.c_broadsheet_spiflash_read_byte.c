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
typedef  int u16 ;
struct broadsheetfb_par {int dummy; } ;

/* Variables and functions */
 int broadsheet_read_reg (struct broadsheetfb_par*,int) ; 
 int broadsheet_spiflash_wait_for_bit (struct broadsheetfb_par*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  broadsheet_write_reg (struct broadsheetfb_par*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int broadsheet_spiflash_read_byte(struct broadsheetfb_par *par, u8 *data)
{
	int err;
	u16 tmp;

	broadsheet_write_reg(par, 0x0202, 0);

	err = broadsheet_spiflash_wait_for_bit(par, 0x0206, 3, 0, 100);
	if (err)
		return err;

	tmp = broadsheet_read_reg(par, 0x200);

	*data = tmp & 0xFF;

	return 0;
}