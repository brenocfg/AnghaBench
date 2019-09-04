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
struct hpi_hw_obj {int /*<<< orphan*/  prHSR; } ;
struct hpi_adapter_obj {struct hpi_hw_obj* priv; } ;

/* Variables and functions */
 int C6205_HSR_INTSRC ; 
 int HPI_IRQ_MIXER ; 
 int HPI_IRQ_NONE ; 
 int ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adapter_irq_query_and_clear(struct hpi_adapter_obj *pao,
	u32 message)
{
	struct hpi_hw_obj *phw = pao->priv;
	u32 hsr = 0;

	hsr = ioread32(phw->prHSR);
	if (hsr & C6205_HSR_INTSRC) {
		/* reset the interrupt from the DSP */
		iowrite32(C6205_HSR_INTSRC, phw->prHSR);
		return HPI_IRQ_MIXER;
	}

	return HPI_IRQ_NONE;
}