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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct xmit_buf {struct submit_ctx* sctx; } ;
struct submit_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int _SUCCESS ; 
 int _rtw_write_port (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_sctx_init (struct submit_ctx*,int) ; 
 int rtw_sctx_wait (struct submit_ctx*) ; 

u32 _rtw_write_port_and_wait(_adapter *adapter, u32 addr, u32 cnt, u8 *pmem, int timeout_ms)
{
	int ret = _SUCCESS;
	struct xmit_buf *pxmitbuf = (struct xmit_buf *)pmem;
	struct submit_ctx sctx;

	rtw_sctx_init(&sctx, timeout_ms);
	pxmitbuf->sctx = &sctx;

	ret = _rtw_write_port(adapter, addr, cnt, pmem);

	if (ret == _SUCCESS)
		ret = rtw_sctx_wait(&sctx);

	 return ret;
}