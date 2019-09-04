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
struct lpfc_vector_map_info {int channel_id; int /*<<< orphan*/  irq; scalar_t__ core_id; scalar_t__ phys_id; } ;
struct TYPE_2__ {int num_present_cpu; struct lpfc_vector_map_info* cpu_map; } ;
struct lpfc_hba {int cfg_fcp_io_channel; int /*<<< orphan*/  pcidev; TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct lpfc_vector_map_info*,int,int) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lpfc_cpu_affinity_check(struct lpfc_hba *phba, int vectors)
{
	struct lpfc_vector_map_info *cpup;
	int index = 0;
	int vec = 0;
	int cpu;
#ifdef CONFIG_X86
	struct cpuinfo_x86 *cpuinfo;
#endif

	/* Init cpu_map array */
	memset(phba->sli4_hba.cpu_map, 0xff,
	       (sizeof(struct lpfc_vector_map_info) *
	       phba->sli4_hba.num_present_cpu));

	/* Update CPU map with physical id and core id of each CPU */
	cpup = phba->sli4_hba.cpu_map;
	for (cpu = 0; cpu < phba->sli4_hba.num_present_cpu; cpu++) {
#ifdef CONFIG_X86
		cpuinfo = &cpu_data(cpu);
		cpup->phys_id = cpuinfo->phys_proc_id;
		cpup->core_id = cpuinfo->cpu_core_id;
#else
		/* No distinction between CPUs for other platforms */
		cpup->phys_id = 0;
		cpup->core_id = 0;
#endif
		cpup->channel_id = index;  /* For now round robin */
		cpup->irq = pci_irq_vector(phba->pcidev, vec);
		vec++;
		if (vec >= vectors)
			vec = 0;
		index++;
		if (index >= phba->cfg_fcp_io_channel)
			index = 0;
		cpup++;
	}
}