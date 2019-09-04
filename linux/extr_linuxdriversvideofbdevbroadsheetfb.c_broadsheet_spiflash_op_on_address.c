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
typedef  int u32 ;
struct broadsheetfb_par {int dummy; } ;

/* Variables and functions */
 int broadsheet_spiflash_write_byte (struct broadsheetfb_par*,int) ; 
 int /*<<< orphan*/  broadsheet_write_reg (struct broadsheetfb_par*,int,int) ; 

__attribute__((used)) static int broadsheet_spiflash_op_on_address(struct broadsheetfb_par *par,
							u8 op, u32 addr)
{
	int i;
	u8 tmp;
	int err;

	broadsheet_write_reg(par, 0x0208, 1);

	err = broadsheet_spiflash_write_byte(par, op);
	if (err)
		return err;

	for (i = 2; i >= 0; i--) {
		tmp = ((addr >> (i * 8)) & 0xFF);
		err = broadsheet_spiflash_write_byte(par, tmp);
		if (err)
			return err;
	}

	return err;
}