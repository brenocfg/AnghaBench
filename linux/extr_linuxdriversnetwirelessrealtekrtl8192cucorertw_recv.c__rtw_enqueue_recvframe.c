#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  list; TYPE_3__* adapter; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
struct recv_priv {int /*<<< orphan*/  free_recvframe_cnt; int /*<<< orphan*/  free_recv_queue; } ;
typedef  int /*<<< orphan*/  sint ;
typedef  int /*<<< orphan*/  _queue ;
struct TYPE_6__ {struct recv_priv recvpriv; } ;
typedef  TYPE_3__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  get_list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_list_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

sint _rtw_enqueue_recvframe(union recv_frame *precvframe, _queue *queue)
{

	_adapter *padapter=precvframe->u.hdr.adapter;
	struct recv_priv *precvpriv = &padapter->recvpriv;

_func_enter_;

	//_rtw_init_listhead(&(precvframe->u.hdr.list));
	rtw_list_delete(&(precvframe->u.hdr.list));


	rtw_list_insert_tail(&(precvframe->u.hdr.list), get_list_head(queue));

	if (padapter != NULL) {
		if (queue == &precvpriv->free_recv_queue)
			precvpriv->free_recvframe_cnt++;
	}

_func_exit_;

	return _SUCCESS;
}