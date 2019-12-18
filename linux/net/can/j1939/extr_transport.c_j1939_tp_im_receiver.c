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
struct j1939_sk_buff_cb {int flags; } ;

/* Variables and functions */
 int J1939_ECU_LOCAL_DST ; 

__attribute__((used)) static inline int j1939_tp_im_receiver(const struct j1939_sk_buff_cb *skcb)
{
	return skcb->flags & J1939_ECU_LOCAL_DST;
}