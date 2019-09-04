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
typedef  int /*<<< orphan*/  u32 ;
struct pkt_attrib {int qsel; } ;
struct xmit_frame {struct pkt_attrib attrib; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCN_QUEUE_INX ; 
 int /*<<< orphan*/  BE_QUEUE_INX ; 
 int /*<<< orphan*/  BK_QUEUE_INX ; 
 int /*<<< orphan*/  HIGH_QUEUE_INX ; 
 int /*<<< orphan*/  MGT_QUEUE_INX ; 
 int /*<<< orphan*/  VI_QUEUE_INX ; 
 int /*<<< orphan*/  VO_QUEUE_INX ; 

u32 rtw_get_ff_hwaddr(struct xmit_frame	*pxmitframe)
{
	u32 addr;
	struct pkt_attrib *pattrib = &pxmitframe->attrib;	
	
	switch(pattrib->qsel)
	{
		case 0:
		case 3:
			addr = BE_QUEUE_INX;
		 	break;
		case 1:
		case 2:
			addr = BK_QUEUE_INX;
			break;				
		case 4:
		case 5:
			addr = VI_QUEUE_INX;
			break;		
		case 6:
		case 7:
			addr = VO_QUEUE_INX;
			break;
		case 0x10:
			addr = BCN_QUEUE_INX;
			break;
		case 0x11://BC/MC in PS (HIQ)
			addr = HIGH_QUEUE_INX;
			break;
		case 0x12:
			addr = MGT_QUEUE_INX;
			break;
		default:
			addr = BE_QUEUE_INX;
			break;		
			
	}

	return addr;

}