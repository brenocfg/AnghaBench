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
struct xmit_priv {int dummy; } ;
struct xmit_frame {scalar_t__ frame_tag; } ;

/* Variables and functions */
 scalar_t__ DATA_FRAMETAG ; 
 int /*<<< orphan*/  r8712_free_xmitframe (struct xmit_priv*,struct xmit_frame*) ; 

void r8712_free_xmitframe_ex(struct xmit_priv *pxmitpriv,
		      struct xmit_frame *pxmitframe)
{
	if (pxmitframe == NULL)
		return;
	if (pxmitframe->frame_tag == DATA_FRAMETAG)
		r8712_free_xmitframe(pxmitpriv, pxmitframe);
}