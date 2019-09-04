#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dvobj_priv {scalar_t__ ishighspeed; int /*<<< orphan*/  RtNumOutPipes; int /*<<< orphan*/  RtNumInPipes; int /*<<< orphan*/ * ep_num; int /*<<< orphan*/  InterfaceNumber; } ;
typedef  int /*<<< orphan*/  _adapter ;
struct TYPE_3__ {int /*<<< orphan*/ * RtBulkOutPipe; int /*<<< orphan*/  RtIntInPipe; int /*<<< orphan*/  RtBulkInPipe; int /*<<< orphan*/  interfaceIndex; int /*<<< orphan*/  UsbBulkOutSize; } ;
typedef  TYPE_1__ HAL_DATA_TYPE ;

/* Variables and functions */
 TYPE_1__* GET_HAL_DATA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HalUsbSetQueuePipeMapping8192CUsb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_FULL_SPEED_BULK_SIZE ; 
 int /*<<< orphan*/  USB_HIGH_SPEED_BULK_SIZE ; 
 scalar_t__ _TRUE ; 
 struct dvobj_priv* adapter_to_dvobj (int /*<<< orphan*/ *) ; 

void rtl8192cu_interface_configure(_adapter *padapter)
{
	HAL_DATA_TYPE	*pHalData	= GET_HAL_DATA(padapter);
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);

	if (pdvobjpriv->ishighspeed == _TRUE)
	{
		pHalData->UsbBulkOutSize = USB_HIGH_SPEED_BULK_SIZE;//512 bytes
	}
	else
	{
		pHalData->UsbBulkOutSize = USB_FULL_SPEED_BULK_SIZE;//64 bytes
	}

	pHalData->interfaceIndex = pdvobjpriv->InterfaceNumber;
	pHalData->RtBulkInPipe = pdvobjpriv->ep_num[0];
	pHalData->RtBulkOutPipe[0] = pdvobjpriv->ep_num[1];
	pHalData->RtBulkOutPipe[1] = pdvobjpriv->ep_num[2];
	pHalData->RtIntInPipe = pdvobjpriv->ep_num[3];
	pHalData->RtBulkOutPipe[2] = pdvobjpriv->ep_num[4];

#ifdef CONFIG_USB_TX_AGGREGATION
	pHalData->UsbTxAggMode		= 1;
	pHalData->UsbTxAggDescNum	= 0x6;	// only 4 bits
#endif

#ifdef CONFIG_USB_RX_AGGREGATION
	pHalData->UsbRxAggMode		= USB_RX_AGG_DMA;// USB_RX_AGG_DMA;
	pHalData->UsbRxAggBlockCount	= 8; //unit : 512b
	pHalData->UsbRxAggBlockTimeout	= 0x6;
	pHalData->UsbRxAggPageCount	= 48; //uint :128 b //0x0A;	// 10 = MAX_RX_DMA_BUFFER_SIZE/2/pHalData->UsbBulkOutSize
	pHalData->UsbRxAggPageTimeout	= 0x4; //6, absolute time = 34ms/(2^6)
#endif

	HalUsbSetQueuePipeMapping8192CUsb(padapter, pdvobjpriv->RtNumInPipes,
		#ifdef CONFIG_USB_ONE_OUT_EP
		1
		#else
		pdvobjpriv->RtNumOutPipes
		#endif
		);

}