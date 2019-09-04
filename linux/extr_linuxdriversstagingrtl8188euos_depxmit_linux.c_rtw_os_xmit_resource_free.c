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
struct xmit_buf {int /*<<< orphan*/  pallocated_buf; int /*<<< orphan*/ * pxmit_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

void rtw_os_xmit_resource_free(struct xmit_buf *pxmitbuf)
{
	int i;

	for (i = 0; i < 8; i++)
		usb_free_urb(pxmitbuf->pxmit_urb[i]);

	kfree(pxmitbuf->pallocated_buf);
}