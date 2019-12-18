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
struct j1939_sk_buff_cb {int dummy; } ;

/* Variables and functions */
 int j1939_tp_im_receiver (struct j1939_sk_buff_cb const*) ; 
 int j1939_tp_im_transmitter (struct j1939_sk_buff_cb const*) ; 

__attribute__((used)) static int j1939_tp_im_involved(const struct j1939_sk_buff_cb *skcb, bool swap)
{
	if (swap)
		return j1939_tp_im_receiver(skcb);
	else
		return j1939_tp_im_transmitter(skcb);
}