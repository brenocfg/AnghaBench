#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct l2cap_conn {TYPE_1__* hcon; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ L2CAP_CID_DYN_END ; 
 scalar_t__ L2CAP_CID_DYN_START ; 
 scalar_t__ L2CAP_CID_LE_DYN_END ; 
 scalar_t__ LE_LINK ; 
 int /*<<< orphan*/  __l2cap_get_chan_by_scid (struct l2cap_conn*,scalar_t__) ; 

__attribute__((used)) static u16 l2cap_alloc_cid(struct l2cap_conn *conn)
{
	u16 cid, dyn_end;

	if (conn->hcon->type == LE_LINK)
		dyn_end = L2CAP_CID_LE_DYN_END;
	else
		dyn_end = L2CAP_CID_DYN_END;

	for (cid = L2CAP_CID_DYN_START; cid <= dyn_end; cid++) {
		if (!__l2cap_get_chan_by_scid(conn, cid))
			return cid;
	}

	return 0;
}