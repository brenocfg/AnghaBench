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
struct ht_priv {int ampdu_enable; int* baddbareq_issued; scalar_t__ ht_option; } ;
struct mlme_priv {struct ht_priv htpriv; } ;
struct _adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  r8712_write8 (struct _adapter*,int,int) ; 

void r8712_joinbss_reset(struct _adapter *padapter)
{
	int i;
	struct mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	struct ht_priv		*phtpriv = &pmlmepriv->htpriv;

	/* todo: if you want to do something io/reg/hw setting before join_bss,
	 * please add code here
	 */
	phtpriv->ampdu_enable = false;/*reset to disabled*/
	for (i = 0; i < 16; i++)
		phtpriv->baddbareq_issued[i] = false;/*reset it*/
	if (phtpriv->ht_option) {
		/* validate  usb rx aggregation */
		r8712_write8(padapter, 0x102500D9, 48);/*TH = 48 pages, 6k*/
	} else {
		/* invalidate  usb rx aggregation */
		/* TH=1 => means that invalidate usb rx aggregation */
		r8712_write8(padapter, 0x102500D9, 1);
	}
}