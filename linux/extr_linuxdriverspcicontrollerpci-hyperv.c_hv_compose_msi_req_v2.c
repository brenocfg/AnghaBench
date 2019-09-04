#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_4__ {int vector_count; int processor_count; int /*<<< orphan*/ * processor_array; int /*<<< orphan*/  delivery_mode; int /*<<< orphan*/  vector; } ;
struct TYPE_6__ {int slot; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct pci_create_interrupt2 {TYPE_1__ int_desc; TYPE_3__ wslot; TYPE_2__ message_type; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CREATE_INTERRUPT_MESSAGE2 ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpumask_first_and (struct cpumask*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dest_Fixed ; 
 int /*<<< orphan*/  hv_cpu_number_to_vp_number (int) ; 

__attribute__((used)) static u32 hv_compose_msi_req_v2(
	struct pci_create_interrupt2 *int_pkt, struct cpumask *affinity,
	u32 slot, u8 vector)
{
	int cpu;

	int_pkt->message_type.type = PCI_CREATE_INTERRUPT_MESSAGE2;
	int_pkt->wslot.slot = slot;
	int_pkt->int_desc.vector = vector;
	int_pkt->int_desc.vector_count = 1;
	int_pkt->int_desc.delivery_mode = dest_Fixed;

	/*
	 * Create MSI w/ dummy vCPU set targeting just one vCPU, overwritten
	 * by subsequent retarget in hv_irq_unmask().
	 */
	cpu = cpumask_first_and(affinity, cpu_online_mask);
	int_pkt->int_desc.processor_array[0] =
		hv_cpu_number_to_vp_number(cpu);
	int_pkt->int_desc.processor_count = 1;

	return sizeof(*int_pkt);
}