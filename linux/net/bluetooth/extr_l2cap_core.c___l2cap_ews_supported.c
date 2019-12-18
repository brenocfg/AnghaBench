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
struct l2cap_conn {int local_fixed_chan; int feat_mask; } ;

/* Variables and functions */
 int L2CAP_FC_A2MP ; 
 int L2CAP_FEAT_EXT_WINDOW ; 

__attribute__((used)) static inline bool __l2cap_ews_supported(struct l2cap_conn *conn)
{
	return ((conn->local_fixed_chan & L2CAP_FC_A2MP) &&
		(conn->feat_mask & L2CAP_FEAT_EXT_WINDOW));
}