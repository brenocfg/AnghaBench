#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  list; TYPE_4__* adapter; } ;
struct TYPE_8__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
struct recv_priv {int /*<<< orphan*/  free_recvframe_cnt; TYPE_3__ free_recv_queue; } ;
typedef  TYPE_3__ _queue ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_10__ {struct recv_priv recvpriv; } ;
typedef  TYPE_4__ _adapter ;

/* Variables and functions */
 int _SUCCESS ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  get_list_head (TYPE_3__*) ; 
 int /*<<< orphan*/  rtw_list_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int rtw_free_recvframe(union recv_frame *precvframe, _queue *pfree_recv_queue)
{
	_irqL irqL;
	_adapter *padapter=precvframe->u.hdr.adapter;
	struct recv_priv *precvpriv = &padapter->recvpriv;

_func_enter_;

#ifdef CONFIG_CONCURRENT_MODE
	if(padapter->adapter_type > PRIMARY_ADAPTER)
	{
		padapter = padapter->pbuddy_adapter;//get primary_padapter
		precvpriv = &padapter->recvpriv;
		pfree_recv_queue = &precvpriv->free_recv_queue;
		precvframe->u.hdr.adapter = padapter;		
	}	
#endif


#ifdef PLATFORM_WINDOWS
	rtw_os_read_port(padapter, precvframe->u.hdr.precvbuf);
#endif

#if defined(PLATFORM_LINUX) || defined(PLATFORM_FREEBSD)

	if(precvframe->u.hdr.pkt)
	{
#ifdef CONFIG_BSD_RX_USE_MBUF
		m_freem(precvframe->u.hdr.pkt);
#else	// CONFIG_BSD_RX_USE_MBUF
		rtw_skb_free(precvframe->u.hdr.pkt);//free skb by driver
#endif	// CONFIG_BSD_RX_USE_MBUF
		precvframe->u.hdr.pkt = NULL;
	}

#endif //defined(PLATFORM_LINUX) || defined(PLATFORM_FREEBSD)

	_enter_critical_bh(&pfree_recv_queue->lock, &irqL);

	rtw_list_delete(&(precvframe->u.hdr.list));

	rtw_list_insert_tail(&(precvframe->u.hdr.list), get_list_head(pfree_recv_queue));

	if(padapter !=NULL){
		if(pfree_recv_queue == &precvpriv->free_recv_queue)
				precvpriv->free_recvframe_cnt++;
	}

      _exit_critical_bh(&pfree_recv_queue->lock, &irqL);

_func_exit_;

	return _SUCCESS;

}