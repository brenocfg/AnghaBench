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
struct recv_buf {scalar_t__ pdata; scalar_t__ pend; scalar_t__ pbuf; scalar_t__ ptail; scalar_t__ phead; scalar_t__ ref_cnt; scalar_t__ len; scalar_t__ transfer_len; } ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_RECVBUF_SZ ; 
 int _SUCCESS ; 

int r8712_init_recvbuf(struct _adapter *padapter, struct recv_buf *precvbuf)
{
	precvbuf->transfer_len = 0;
	precvbuf->len = 0;
	precvbuf->ref_cnt = 0;
	if (precvbuf->pbuf) {
		precvbuf->pdata = precvbuf->pbuf;
		precvbuf->phead = precvbuf->pbuf;
		precvbuf->ptail = precvbuf->pbuf;
		precvbuf->pend = precvbuf->pdata + MAX_RECVBUF_SZ;
	}
	return _SUCCESS;
}