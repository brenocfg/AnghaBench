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
typedef  int /*<<< orphan*/  u16 ;
struct broadsheetfb_par {int dummy; } ;

/* Variables and functions */
 int broadsheet_setup_plls (struct broadsheetfb_par*) ; 
 int broadsheet_setup_spi (struct broadsheetfb_par*) ; 
 int broadsheet_setup_spiflash (struct broadsheetfb_par*,int /*<<< orphan*/ *) ; 
 int broadsheet_verify_spiflash (struct broadsheetfb_par*,int*) ; 
 int /*<<< orphan*/  broadsheet_write_reg (struct broadsheetfb_par*,int,int) ; 

__attribute__((used)) static int broadsheet_setup_for_wfm_write(struct broadsheetfb_par *par,
					u16 *initial_sfmcd, int *flash_type)

{
	int err;

	err = broadsheet_setup_plls(par);
	if (err)
		return err;

	broadsheet_write_reg(par, 0x0106, 0x0203);

	err = broadsheet_setup_spi(par);
	if (err)
		return err;

	err = broadsheet_setup_spiflash(par, initial_sfmcd);
	if (err)
		return err;

	return broadsheet_verify_spiflash(par, flash_type);
}