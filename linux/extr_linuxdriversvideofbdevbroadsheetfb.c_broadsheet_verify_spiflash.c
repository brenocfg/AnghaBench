#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct broadsheetfb_par {TYPE_1__* info; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EINVAL ; 
 int broadsheet_spiflash_op_on_address (struct broadsheetfb_par*,int,int) ; 
 int broadsheet_spiflash_read_byte (struct broadsheetfb_par*,int*) ; 
 int /*<<< orphan*/  broadsheet_write_reg (struct broadsheetfb_par*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int broadsheet_verify_spiflash(struct broadsheetfb_par *par,
						int *flash_type)
{
	int err = 0;
	u8 sig;

	err = broadsheet_spiflash_op_on_address(par, 0xAB, 0x00000000);
	if (err)
		goto failout;

	err = broadsheet_spiflash_read_byte(par, &sig);
	if (err)
		goto failout;

	if ((sig != 0x10) && (sig != 0x11)) {
		dev_err(par->info->device, "Unexpected flash type\n");
		err = -EINVAL;
		goto failout;
	}

	*flash_type = sig;

failout:
	broadsheet_write_reg(par, 0x0208, 0);
	return err;
}