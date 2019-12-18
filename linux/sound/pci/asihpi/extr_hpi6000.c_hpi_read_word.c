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
typedef  int /*<<< orphan*/  u32 ;
struct dsp_obj {int /*<<< orphan*/  prHPI_data; } ;

/* Variables and functions */
 scalar_t__ hpi_set_address (struct dsp_obj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 hpi_read_word(struct dsp_obj *pdo, u32 address)
{
	u32 data = 0;

	if (hpi_set_address(pdo, address))
		return 0;	/*? No way to return error */

	/* take care of errata in revB DSP (2.0.1) */
	data = ioread32(pdo->prHPI_data);
	return data;
}