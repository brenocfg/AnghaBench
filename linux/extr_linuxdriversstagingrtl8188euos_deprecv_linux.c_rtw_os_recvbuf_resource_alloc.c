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
struct recv_buf {int reuse; int /*<<< orphan*/  purb; int /*<<< orphan*/ * pskb; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rtw_os_recvbuf_resource_alloc(struct adapter *padapter,
				  struct recv_buf *precvbuf)
{
	precvbuf->pskb = NULL;
	precvbuf->reuse = false;
	precvbuf->purb = usb_alloc_urb(0, GFP_KERNEL);
	if (!precvbuf->purb)
		return _FAIL;
	return _SUCCESS;
}