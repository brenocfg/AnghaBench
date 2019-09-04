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
struct TYPE_2__ {int input; int output; int sync; int sync_after_ai; int sync_out_after_pci; } ;
struct qdio_irq {TYPE_1__ siga_flag; } ;

/* Variables and functions */
 unsigned char AC1_AUTOMATIC_SYNC_ON_OUT_PCI ; 
 unsigned char AC1_AUTOMATIC_SYNC_ON_THININT ; 
 unsigned char AC1_SIGA_INPUT_NEEDED ; 
 unsigned char AC1_SIGA_OUTPUT_NEEDED ; 
 unsigned char AC1_SIGA_SYNC_NEEDED ; 

__attribute__((used)) static void process_ac_flags(struct qdio_irq *irq_ptr, unsigned char qdioac)
{
	if (qdioac & AC1_SIGA_INPUT_NEEDED)
		irq_ptr->siga_flag.input = 1;
	if (qdioac & AC1_SIGA_OUTPUT_NEEDED)
		irq_ptr->siga_flag.output = 1;
	if (qdioac & AC1_SIGA_SYNC_NEEDED)
		irq_ptr->siga_flag.sync = 1;
	if (!(qdioac & AC1_AUTOMATIC_SYNC_ON_THININT))
		irq_ptr->siga_flag.sync_after_ai = 1;
	if (!(qdioac & AC1_AUTOMATIC_SYNC_ON_OUT_PCI))
		irq_ptr->siga_flag.sync_out_after_pci = 1;
}