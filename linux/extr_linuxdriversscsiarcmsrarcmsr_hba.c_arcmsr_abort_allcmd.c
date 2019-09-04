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
typedef  int /*<<< orphan*/  uint8_t ;
struct AdapterControlBlock {int adapter_type; } ;

/* Variables and functions */
#define  ACB_ADAPTER_TYPE_A 132 
#define  ACB_ADAPTER_TYPE_B 131 
#define  ACB_ADAPTER_TYPE_C 130 
#define  ACB_ADAPTER_TYPE_D 129 
#define  ACB_ADAPTER_TYPE_E 128 
 int /*<<< orphan*/  arcmsr_hbaA_abort_allcmd (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_hbaB_abort_allcmd (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_hbaC_abort_allcmd (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_hbaD_abort_allcmd (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_hbaE_abort_allcmd (struct AdapterControlBlock*) ; 

__attribute__((used)) static uint8_t arcmsr_abort_allcmd(struct AdapterControlBlock *acb)
{
	uint8_t rtnval = 0;
	switch (acb->adapter_type) {
	case ACB_ADAPTER_TYPE_A: {
		rtnval = arcmsr_hbaA_abort_allcmd(acb);
		}
		break;

	case ACB_ADAPTER_TYPE_B: {
		rtnval = arcmsr_hbaB_abort_allcmd(acb);
		}
		break;

	case ACB_ADAPTER_TYPE_C: {
		rtnval = arcmsr_hbaC_abort_allcmd(acb);
		}
		break;

	case ACB_ADAPTER_TYPE_D:
		rtnval = arcmsr_hbaD_abort_allcmd(acb);
		break;
	case ACB_ADAPTER_TYPE_E:
		rtnval = arcmsr_hbaE_abort_allcmd(acb);
		break;
	}
	return rtnval;
}