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
struct zero_bulkout_context {scalar_t__ pirp; struct zero_bulkout_context* purb; struct zero_bulkout_context* pbuf; } ;
typedef  scalar_t__ PIRP ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreePool (struct zero_bulkout_context*) ; 
 int /*<<< orphan*/  IoFreeIrp (scalar_t__) ; 
 int /*<<< orphan*/  STATUS_MORE_PROCESSING_REQUIRED ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 

NTSTATUS usb_bulkout_zero_complete(
	PDEVICE_OBJECT	pUsbDevObj, 
	PIRP		pIrp, void*	pZeroContext)
{	
	struct zero_bulkout_context *pcontext = (struct zero_bulkout_context *)pZeroContext;
			   
_func_enter_;

	if(pcontext)
	{
		if(pcontext->pbuf)
		{
			ExFreePool(pcontext->pbuf);	  
		}	

		if(pcontext->purb)
		{
			ExFreePool(pcontext->purb);	
		}

		if(pcontext->pirp && (pIrp ==pcontext->pirp))
		{			
			IoFreeIrp(pIrp);
		}

		ExFreePool(pcontext);	
	}	

_func_exit_;

	return STATUS_MORE_PROCESSING_REQUIRED;
	

}