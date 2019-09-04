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
typedef  scalar_t__ u32 ;
struct xmit_buf {int /*<<< orphan*/  pallocated_buf; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void rtw_os_xmit_resource_free(struct adapter *padapter, struct xmit_buf *pxmitbuf, u32 free_sz, u8 flag)
{
	if (free_sz > 0)
		kfree(pxmitbuf->pallocated_buf);
}