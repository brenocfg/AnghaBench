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
struct AdapterControlBlock {int adapter_type; int /*<<< orphan*/  pmuE; int /*<<< orphan*/  mem_base0; int /*<<< orphan*/  pmuC; int /*<<< orphan*/  mem_base1; int /*<<< orphan*/  pmuA; } ;

/* Variables and functions */
#define  ACB_ADAPTER_TYPE_A 132 
#define  ACB_ADAPTER_TYPE_B 131 
#define  ACB_ADAPTER_TYPE_C 130 
#define  ACB_ADAPTER_TYPE_D 129 
#define  ACB_ADAPTER_TYPE_E 128 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arcmsr_unmap_pciregion(struct AdapterControlBlock *acb)
{
	switch (acb->adapter_type) {
	case ACB_ADAPTER_TYPE_A:{
		iounmap(acb->pmuA);
	}
	break;
	case ACB_ADAPTER_TYPE_B:{
		iounmap(acb->mem_base0);
		iounmap(acb->mem_base1);
	}

	break;
	case ACB_ADAPTER_TYPE_C:{
		iounmap(acb->pmuC);
	}
	break;
	case ACB_ADAPTER_TYPE_D:
		iounmap(acb->mem_base0);
		break;
	case ACB_ADAPTER_TYPE_E:
		iounmap(acb->pmuE);
		break;
	}
}