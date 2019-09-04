#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct dvobj_priv {int nr_endpoint; TYPE_2__* padapter; } ;
struct TYPE_3__ {void** pipehdls_r8712; } ;
struct TYPE_4__ {TYPE_1__ halpriv; } ;
typedef  TYPE_2__ _adapter ;
typedef  void* HANDLE ;

/* Variables and functions */
#define  RTL8712_DMA_BCNQ 137 
#define  RTL8712_DMA_BEQ 136 
#define  RTL8712_DMA_BKQ 135 
#define  RTL8712_DMA_BMCQ 134 
#define  RTL8712_DMA_C2HCMD 133 
#define  RTL8712_DMA_H2CCMD 132 
#define  RTL8712_DMA_MGTQ 131 
#define  RTL8712_DMA_RX0FF 130 
#define  RTL8712_DMA_VIQ 129 
#define  RTL8712_DMA_VOQ 128 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 

void *ffaddr2pipehdl(struct dvobj_priv *pNdisCEDvice, u32 addr)
{
	HANDLE PipeHandle = NULL;
	_adapter	*padapter = pNdisCEDvice->padapter;

	
	if(pNdisCEDvice->nr_endpoint == 11)
	{		
		switch(addr)
		{	    
	     		case RTL8712_DMA_BEQ:
		 		PipeHandle= padapter->halpriv.pipehdls_r8712[3] ; 
				break;
	     		case RTL8712_DMA_BKQ:
			 	PipeHandle=  padapter->halpriv.pipehdls_r8712[4]; 
				break;
	     		case RTL8712_DMA_VIQ:
		 		PipeHandle=  padapter->halpriv.pipehdls_r8712[2]; 
				break;
	    		case RTL8712_DMA_VOQ:
				PipeHandle=  padapter->halpriv.pipehdls_r8712[1]; 
				break;					
                     case RTL8712_DMA_BCNQ:	
				PipeHandle=  padapter->halpriv.pipehdls_r8712[6]; 
				break;	 	
			case RTL8712_DMA_BMCQ:	//HI Queue
				PipeHandle=  padapter->halpriv.pipehdls_r8712[7]; 
				break;	
			case RTL8712_DMA_MGTQ:				
		 		PipeHandle=  padapter->halpriv.pipehdls_r8712[8]; 
				break;
                     case RTL8712_DMA_RX0FF:
				PipeHandle=  padapter->halpriv.pipehdls_r8712[0]; 
				break;	 	
			case RTL8712_DMA_C2HCMD:		 	
				PipeHandle=  padapter->halpriv.pipehdls_r8712[5]; 
				break;
			case RTL8712_DMA_H2CCMD:
				PipeHandle=  padapter->halpriv.pipehdls_r8712[9]; 
				break;	
				
		}

	}
	else if(pNdisCEDvice->nr_endpoint == 6)
	{
		switch(addr)
		{	    
	     		case RTL8712_DMA_BEQ:
		 		PipeHandle=  padapter->halpriv.pipehdls_r8712[3]; 
				break;
	     		case RTL8712_DMA_BKQ:
			 	PipeHandle=  padapter->halpriv.pipehdls_r8712[4]; 
				break;
	     		case RTL8712_DMA_VIQ:
		 		PipeHandle=  padapter->halpriv.pipehdls_r8712[2]; 
				break;
	    		case RTL8712_DMA_VOQ:                   		
		 		PipeHandle=  padapter->halpriv.pipehdls_r8712[1]; 
				break;
                     case RTL8712_DMA_RX0FF:
			case RTL8712_DMA_C2HCMD:		 	
				PipeHandle=  padapter->halpriv.pipehdls_r8712[0]; 
				break;
			case RTL8712_DMA_H2CCMD:
			case RTL8712_DMA_BCNQ:					
			case RTL8712_DMA_BMCQ:	
			case RTL8712_DMA_MGTQ:			
				PipeHandle=  padapter->halpriv.pipehdls_r8712[5]; 
				break;	
				
		}

	}
	else if(pNdisCEDvice->nr_endpoint == 4)
	{
		switch(addr)
		{		
	     		case RTL8712_DMA_BEQ:
		 	//case RTL8712_DMA_BKQ:
			 	PipeHandle=  padapter->halpriv.pipehdls_r8712[2]; 
				break;
	     		//case RTL8712_DMA_VIQ:
		 	case RTL8712_DMA_VOQ:					
		 		PipeHandle=  padapter->halpriv.pipehdls_r8712[1]; 
				break;
			case RTL8712_DMA_RX0FF:
			case RTL8712_DMA_C2HCMD:		 	
				PipeHandle=  padapter->halpriv.pipehdls_r8712[0]; 
				break;
			case RTL8712_DMA_H2CCMD:	
			case RTL8712_DMA_BCNQ:					
			case RTL8712_DMA_BMCQ:	
			case RTL8712_DMA_MGTQ:				
				PipeHandle=  padapter->halpriv.pipehdls_r8712[3]; 
				break;	
		}
	
	}
	else
	{
	   RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("ffaddr2pipehdl():nr_endpoint=%d error!\n", pNdisCEDvice->nr_endpoint));	   
	}
		
	return PipeHandle;

}