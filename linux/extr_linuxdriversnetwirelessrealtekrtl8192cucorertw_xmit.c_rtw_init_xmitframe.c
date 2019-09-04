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
struct xmit_frame {int /*<<< orphan*/  frame_tag; int /*<<< orphan*/  attrib; int /*<<< orphan*/ * pxmitbuf; int /*<<< orphan*/ * buf_addr; } ;
struct pkt_attrib {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_FRAMETAG ; 
 int /*<<< orphan*/  _rtw_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void rtw_init_xmitframe(struct xmit_frame *pxframe)
{
	if (pxframe !=  NULL)//default value setting
	{
		pxframe->buf_addr = NULL;
		pxframe->pxmitbuf = NULL;

		_rtw_memset(&pxframe->attrib, 0, sizeof(struct pkt_attrib));
		//pxframe->attrib.psta = NULL;

		pxframe->frame_tag = DATA_FRAMETAG;

#ifdef CONFIG_USB_HCI
		pxframe->pkt = NULL;
		pxframe->pkt_offset = 1;//default use pkt_offset to fill tx desc

#ifdef CONFIG_USB_TX_AGGREGATION
		pxframe->agg_num = 1;
#endif

#endif //#ifdef CONFIG_USB_HCI

#if defined(CONFIG_SDIO_HCI) || defined(CONFIG_GSPI_HCI)
		pxframe->pg_num = 1;
		pxframe->agg_num = 1;
#endif

#ifdef CONFIG_XMIT_ACK
		pxframe->ack_report = 0;
#endif

	}
}