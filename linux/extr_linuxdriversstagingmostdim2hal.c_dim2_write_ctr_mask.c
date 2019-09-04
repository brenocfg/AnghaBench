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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {TYPE_1__* dim2; } ;
struct TYPE_3__ {int /*<<< orphan*/  MDWE3; int /*<<< orphan*/  MDWE2; int /*<<< orphan*/  MDWE1; int /*<<< orphan*/  MDWE0; int /*<<< orphan*/  MDAT3; int /*<<< orphan*/  MDAT2; int /*<<< orphan*/  MDAT1; int /*<<< orphan*/  MDAT0; int /*<<< orphan*/  MCTL; } ;

/* Variables and functions */
 scalar_t__ bit_mask (int) ; 
 int /*<<< orphan*/  dim2_transfer_madr (scalar_t__) ; 
 int /*<<< orphan*/  dimcb_io_write (int /*<<< orphan*/ *,scalar_t__ const) ; 
 TYPE_2__ g ; 

__attribute__((used)) static void dim2_write_ctr_mask(u32 ctr_addr, const u32 *mask, const u32 *value)
{
	enum { MADR_WNR_BIT = 31 };

	dimcb_io_write(&g.dim2->MCTL, 0);   /* clear transfer complete */

	if (mask[0] != 0)
		dimcb_io_write(&g.dim2->MDAT0, value[0]);
	if (mask[1] != 0)
		dimcb_io_write(&g.dim2->MDAT1, value[1]);
	if (mask[2] != 0)
		dimcb_io_write(&g.dim2->MDAT2, value[2]);
	if (mask[3] != 0)
		dimcb_io_write(&g.dim2->MDAT3, value[3]);

	dimcb_io_write(&g.dim2->MDWE0, mask[0]);
	dimcb_io_write(&g.dim2->MDWE1, mask[1]);
	dimcb_io_write(&g.dim2->MDWE2, mask[2]);
	dimcb_io_write(&g.dim2->MDWE3, mask[3]);

	dim2_transfer_madr(bit_mask(MADR_WNR_BIT) | ctr_addr);
}