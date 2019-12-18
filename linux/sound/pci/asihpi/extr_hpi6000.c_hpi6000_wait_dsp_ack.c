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
struct dsp_obj {int /*<<< orphan*/  prHPI_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  H6READ ; 
 int /*<<< orphan*/  HPI_HIF_ADDR (int /*<<< orphan*/ ) ; 
 short HPI_HIF_ERROR_MASK ; 
 int TIMEOUT ; 
 int /*<<< orphan*/  dsp_ack ; 
 int /*<<< orphan*/  hpi6000_check_PCI2040_error_flag (struct hpi_adapter_obj*,int /*<<< orphan*/ ) ; 
 int hpi_read_word (struct dsp_obj*,int /*<<< orphan*/ ) ; 
 int ioread32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static short hpi6000_wait_dsp_ack(struct hpi_adapter_obj *pao, u16 dsp_index,
	u32 ack_value)
{
	struct hpi_hw_obj *phw = pao->priv;
	struct dsp_obj *pdo = &phw->ado[dsp_index];
	u32 ack = 0L;
	u32 timeout;
	u32 hPIC = 0L;

	/* wait for host interrupt to signal ack is ready */
	timeout = TIMEOUT;
	while (--timeout) {
		hPIC = ioread32(pdo->prHPI_control);
		if (hPIC & 0x04)	/* 0x04 = HINT from DSP */
			break;
	}
	if (timeout == 0)
		return HPI_HIF_ERROR_MASK;

	/* wait for dwAckValue */
	timeout = TIMEOUT;
	while (--timeout) {
		/* read the ack mailbox */
		ack = hpi_read_word(pdo, HPI_HIF_ADDR(dsp_ack));
		if (ack == ack_value)
			break;
		if ((ack & HPI_HIF_ERROR_MASK)
			&& !hpi6000_check_PCI2040_error_flag(pao, H6READ))
			break;
		/*for (i=0;i<1000;i++) */
		/*      dwPause=i+1; */
	}
	if (ack & HPI_HIF_ERROR_MASK)
		/* indicates bad read from DSP -
		   typically 0xffffff is read for some reason */
		ack = HPI_HIF_ERROR_MASK;

	if (timeout == 0)
		ack = HPI_HIF_ERROR_MASK;
	return (short)ack;
}