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
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct hdlc_header {void* protocol; int /*<<< orphan*/  control; int /*<<< orphan*/  address; } ;

/* Variables and functions */
#define  ETH_P_IP 132 
#define  ETH_P_IPV6 131 
 int /*<<< orphan*/  HDLC_ADDR_ALLSTATIONS ; 
 int /*<<< orphan*/  HDLC_CTRL_UI ; 
 int PID_IP ; 
#define  PID_IPCP 130 
 int PID_IPV6 ; 
#define  PID_IPV6CP 129 
#define  PID_LCP 128 
 void* htons (int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static int ppp_hard_header(struct sk_buff *skb, struct net_device *dev,
			   u16 type, const void *daddr, const void *saddr,
			   unsigned int len)
{
	struct hdlc_header *data;
#if DEBUG_HARD_HEADER
	printk(KERN_DEBUG "%s: ppp_hard_header() called\n", dev->name);
#endif

	skb_push(skb, sizeof(struct hdlc_header));
	data = (struct hdlc_header*)skb->data;

	data->address = HDLC_ADDR_ALLSTATIONS;
	data->control = HDLC_CTRL_UI;
	switch (type) {
	case ETH_P_IP:
		data->protocol = htons(PID_IP);
		break;
	case ETH_P_IPV6:
		data->protocol = htons(PID_IPV6);
		break;
	case PID_LCP:
	case PID_IPCP:
	case PID_IPV6CP:
		data->protocol = htons(type);
		break;
	default:		/* unknown protocol */
		data->protocol = 0;
	}
	return sizeof(struct hdlc_header);
}