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
struct sk_buff {int dummy; } ;
struct recv_priv {int /*<<< orphan*/  free_recv_skb_queue; int /*<<< orphan*/  rx_skb_queue; struct recv_buf* precv_buf; int /*<<< orphan*/  free_recv_buf_queue; int /*<<< orphan*/  recv_tasklet; } ;
struct recv_buf {struct adapter* adapter; } ;
struct adapter {int /*<<< orphan*/  pnetdev; struct recv_priv recvpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_RECVBUF_SZ ; 
 int NR_PREALLOC_RECV_SKB ; 
 int NR_RECVBUFF ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _FAIL ; 
 int _SUCCESS ; 
 struct sk_buff* __netdev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int /*<<< orphan*/  _rtw_init_queue (int /*<<< orphan*/ *) ; 
 struct recv_buf* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemleak_not_leak (struct sk_buff*) ; 
 scalar_t__ rtl8188eu_recv_tasklet ; 
 int rtw_os_recvbuf_resource_alloc (struct adapter*,struct recv_buf*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,void (*) (unsigned long),unsigned long) ; 

int	rtw_hal_init_recv_priv(struct adapter *padapter)
{
	struct recv_priv	*precvpriv = &padapter->recvpriv;
	int	i, res = _SUCCESS;
	struct recv_buf *precvbuf;

	tasklet_init(&precvpriv->recv_tasklet,
		     (void(*)(unsigned long))rtl8188eu_recv_tasklet,
		     (unsigned long)padapter);

	/* init recv_buf */
	_rtw_init_queue(&precvpriv->free_recv_buf_queue);

	precvpriv->precv_buf =
		kcalloc(NR_RECVBUFF, sizeof(struct recv_buf), GFP_KERNEL);
	if (!precvpriv->precv_buf) {
		res = _FAIL;
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_,
				("alloc recv_buf fail!\n"));
		goto exit;
	}
	precvbuf = precvpriv->precv_buf;

	for (i = 0; i < NR_RECVBUFF; i++) {
		res = rtw_os_recvbuf_resource_alloc(padapter, precvbuf);
		if (res == _FAIL)
			break;
		precvbuf->adapter = padapter;
		precvbuf++;
	}
	skb_queue_head_init(&precvpriv->rx_skb_queue);
	{
		int i;
		struct sk_buff *pskb = NULL;

		skb_queue_head_init(&precvpriv->free_recv_skb_queue);

		for (i = 0; i < NR_PREALLOC_RECV_SKB; i++) {
			pskb = __netdev_alloc_skb(padapter->pnetdev,
					MAX_RECVBUF_SZ, GFP_KERNEL);
			if (pskb) {
				kmemleak_not_leak(pskb);
				skb_queue_tail(&precvpriv->free_recv_skb_queue,
						pskb);
			}
			pskb = NULL;
		}
	}
exit:
	return res;
}