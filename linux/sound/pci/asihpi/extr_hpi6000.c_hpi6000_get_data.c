#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  long u32 ;
typedef  size_t u16 ;
struct hpi_response {int dummy; } ;
struct TYPE_5__ {long data_size; scalar_t__ pb_data; } ;
struct TYPE_6__ {TYPE_1__ data; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ d; } ;
struct hpi_message {TYPE_4__ u; } ;
struct hpi_hw_obj {struct dsp_obj* ado; } ;
struct hpi_adapter_obj {struct hpi_hw_obj* priv; } ;
struct dsp_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H6READ ; 
 short HPI6000_ERROR_GET_DATA_ACK ; 
 short HPI6000_ERROR_GET_DATA_CMD ; 
 short HPI6000_ERROR_GET_DATA_IDLECMD ; 
 short HPI6000_ERROR_GET_DATA_IDLE_TIMEOUT ; 
 short HPI6000_ERROR_GET_DATA_READ ; 
 int /*<<< orphan*/  HPI_HIF_ADDR (long) ; 
 size_t HPI_HIF_ERROR_MASK ; 
 int /*<<< orphan*/  HPI_HIF_GET_DATA ; 
 int /*<<< orphan*/  HPI_HIF_IDLE ; 
 scalar_t__ hpi6000_check_PCI2040_error_flag (struct hpi_adapter_obj*,int /*<<< orphan*/ ) ; 
 scalar_t__ hpi6000_dsp_block_read32 (struct hpi_adapter_obj*,size_t,long,long*,long) ; 
 int /*<<< orphan*/  hpi6000_send_dsp_interrupt (struct dsp_obj*) ; 
 scalar_t__ hpi6000_send_host_command (struct hpi_adapter_obj*,size_t,int /*<<< orphan*/ ) ; 
 size_t hpi6000_wait_dsp_ack (struct hpi_adapter_obj*,size_t,int /*<<< orphan*/ ) ; 
 long hpi_read_word (struct dsp_obj*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static short hpi6000_get_data(struct hpi_adapter_obj *pao, u16 dsp_index,
	struct hpi_message *phm, struct hpi_response *phr)
{
	struct hpi_hw_obj *phw = pao->priv;
	struct dsp_obj *pdo = &phw->ado[dsp_index];
	u32 data_got = 0;
	u16 ack;
	u32 length, address;
	u32 *p_data = (u32 *)phm->u.d.u.data.pb_data;

	(void)phr;	/* this parameter not used! */

	/* round dwDataSize down to nearest 4 bytes */
	while (data_got < (phm->u.d.u.data.data_size & ~3L)) {
		ack = hpi6000_wait_dsp_ack(pao, dsp_index, HPI_HIF_IDLE);
		if (ack & HPI_HIF_ERROR_MASK)
			return HPI6000_ERROR_GET_DATA_IDLE_TIMEOUT;

		if (hpi6000_send_host_command(pao, dsp_index,
				HPI_HIF_GET_DATA))
			return HPI6000_ERROR_GET_DATA_CMD;
		hpi6000_send_dsp_interrupt(pdo);

		ack = hpi6000_wait_dsp_ack(pao, dsp_index, HPI_HIF_GET_DATA);

		if (ack & HPI_HIF_ERROR_MASK)
			return HPI6000_ERROR_GET_DATA_ACK;

		/* get the address and size */
		do {
			address = hpi_read_word(pdo, HPI_HIF_ADDR(address));
			length = hpi_read_word(pdo, HPI_HIF_ADDR(length));
		} while (hpi6000_check_PCI2040_error_flag(pao, H6READ));

		/* read the data */
		{
			u32 len = length;
			u32 blk_len = 512;
			while (len) {
				if (len < blk_len)
					blk_len = len;
				if (hpi6000_dsp_block_read32(pao, dsp_index,
						address, p_data, blk_len))
					return HPI6000_ERROR_GET_DATA_READ;
				address += blk_len * 4;
				p_data += blk_len;
				len -= blk_len;
			}
		}

		if (hpi6000_send_host_command(pao, dsp_index, HPI_HIF_IDLE))
			return HPI6000_ERROR_GET_DATA_IDLECMD;
		hpi6000_send_dsp_interrupt(pdo);

		data_got += length * 4;
	}
	return 0;
}