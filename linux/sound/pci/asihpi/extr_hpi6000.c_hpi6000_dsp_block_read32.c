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
typedef  int u32 ;
typedef  size_t u16 ;
struct hpi_hw_obj {struct dsp_obj* ado; } ;
struct hpi_adapter_obj {struct hpi_hw_obj* priv; } ;
struct dsp_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H6READ ; 
 int PCI_TIMEOUT ; 
 scalar_t__ hpi6000_check_PCI2040_error_flag (struct hpi_adapter_obj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_read_block (struct dsp_obj*,int,int*,int) ; 

__attribute__((used)) static u16 hpi6000_dsp_block_read32(struct hpi_adapter_obj *pao,
	u16 dsp_index, u32 hpi_address, u32 *dest, u32 count)
{
	struct hpi_hw_obj *phw = pao->priv;
	struct dsp_obj *pdo = &phw->ado[dsp_index];
	u32 time_out = PCI_TIMEOUT;
	int c6711_burst_size = 16;
	u32 local_hpi_address = hpi_address;
	int local_count = count;
	int xfer_size;
	u32 *pdata = dest;
	u32 loop_count = 0;

	while (local_count) {
		if (local_count > c6711_burst_size)
			xfer_size = c6711_burst_size;
		else
			xfer_size = local_count;

		time_out = PCI_TIMEOUT;
		do {
			hpi_read_block(pdo, local_hpi_address, pdata,
				xfer_size);
		} while (hpi6000_check_PCI2040_error_flag(pao, H6READ)
			&& --time_out);
		if (!time_out)
			break;

		pdata += xfer_size;
		local_hpi_address += sizeof(u32) * xfer_size;
		local_count -= xfer_size;
		loop_count++;
	}

	if (time_out)
		return 0;
	else
		return 1;
}