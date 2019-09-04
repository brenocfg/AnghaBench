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
struct xmit_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _TRUE ; 
 struct xmit_frame* _alloc_mgtxmitframe (struct xmit_priv*,int /*<<< orphan*/ ) ; 

inline struct xmit_frame *alloc_mgtxmitframe_once(struct xmit_priv *pxmitpriv)
{
	return _alloc_mgtxmitframe(pxmitpriv, _TRUE);
}