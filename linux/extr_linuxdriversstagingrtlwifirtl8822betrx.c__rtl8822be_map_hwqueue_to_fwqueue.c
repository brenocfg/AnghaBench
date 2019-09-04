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
typedef  int u8 ;
struct sk_buff {int priority; } ;

/* Variables and functions */
#define  BEACON_QUEUE 131 
#define  H2C_QUEUE 130 
#define  HIGH_QUEUE 129 
#define  MGNT_QUEUE 128 
 int QSLT_BEACON ; 
 int QSLT_CMD ; 
 int QSLT_HIGH ; 
 int QSLT_MGNT ; 

__attribute__((used)) static u8 _rtl8822be_map_hwqueue_to_fwqueue(struct sk_buff *skb, u8 hw_queue)
{
	switch (hw_queue) {
	case BEACON_QUEUE:
		return QSLT_BEACON;
	case H2C_QUEUE:
		return QSLT_CMD;
	case MGNT_QUEUE:
		return QSLT_MGNT;
	case HIGH_QUEUE:
		return QSLT_HIGH;
	default:
		return skb->priority;
	}
}