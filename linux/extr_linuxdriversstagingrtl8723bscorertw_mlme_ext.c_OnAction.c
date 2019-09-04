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
struct TYPE_3__ {int /*<<< orphan*/ * rx_data; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_hdr_3addr {int dummy; } ;
struct adapter {int dummy; } ;
struct action_handler {unsigned char num; int /*<<< orphan*/  (* func ) (struct adapter*,union recv_frame*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (struct action_handler*) ; 
 struct action_handler* OnAction_tbl ; 
 unsigned int _SUCCESS ; 
 int /*<<< orphan*/  stub1 (struct adapter*,union recv_frame*) ; 

unsigned int OnAction(struct adapter *padapter, union recv_frame *precv_frame)
{
	int i;
	unsigned char category;
	struct action_handler *ptable;
	unsigned char *frame_body;
	u8 *pframe = precv_frame->u.hdr.rx_data;

	frame_body = (unsigned char *)(pframe + sizeof(struct ieee80211_hdr_3addr));

	category = frame_body[0];

	for (i = 0; i < ARRAY_SIZE(OnAction_tbl); i++) {
		ptable = &OnAction_tbl[i];

		if (category == ptable->num)
			ptable->func(padapter, precv_frame);

	}

	return _SUCCESS;

}