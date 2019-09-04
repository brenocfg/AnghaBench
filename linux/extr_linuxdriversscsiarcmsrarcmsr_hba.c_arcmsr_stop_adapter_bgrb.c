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
struct AdapterControlBlock {int adapter_type; } ;

/* Variables and functions */
#define  ACB_ADAPTER_TYPE_A 132 
#define  ACB_ADAPTER_TYPE_B 131 
#define  ACB_ADAPTER_TYPE_C 130 
#define  ACB_ADAPTER_TYPE_D 129 
#define  ACB_ADAPTER_TYPE_E 128 
 int /*<<< orphan*/  arcmsr_hbaA_stop_bgrb (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_hbaB_stop_bgrb (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_hbaC_stop_bgrb (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_hbaD_stop_bgrb (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_hbaE_stop_bgrb (struct AdapterControlBlock*) ; 

__attribute__((used)) static void arcmsr_stop_adapter_bgrb(struct AdapterControlBlock *acb)
{
	switch (acb->adapter_type) {
	case ACB_ADAPTER_TYPE_A: {
		arcmsr_hbaA_stop_bgrb(acb);
		}
		break;

	case ACB_ADAPTER_TYPE_B: {
		arcmsr_hbaB_stop_bgrb(acb);
		}
		break;
	case ACB_ADAPTER_TYPE_C: {
		arcmsr_hbaC_stop_bgrb(acb);
		}
		break;
	case ACB_ADAPTER_TYPE_D:
		arcmsr_hbaD_stop_bgrb(acb);
		break;
	case ACB_ADAPTER_TYPE_E:
		arcmsr_hbaE_stop_bgrb(acb);
		break;
	}
}