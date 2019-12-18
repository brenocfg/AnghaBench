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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct dsp_obj {int /*<<< orphan*/  prHPI_data; int /*<<< orphan*/  prHPI_data_auto_inc; } ;

/* Variables and functions */
 scalar_t__ hpi_set_address (struct dsp_obj*,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32_rep (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static void hpi_write_block(struct dsp_obj *pdo, u32 address, u32 *pdata,
	u32 length)
{
	u16 length16 = length - 1;

	if (length == 0)
		return;

	if (hpi_set_address(pdo, address))
		return;

	iowrite32_rep(pdo->prHPI_data_auto_inc, pdata, length16);

	/* take care of errata in revB DSP (2.0.1) */
	/* must end with non auto-inc */
	iowrite32(*(pdata + length - 1), pdo->prHPI_data);
}