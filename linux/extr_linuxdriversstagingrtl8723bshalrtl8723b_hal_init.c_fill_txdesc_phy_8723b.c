#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pkt_attrib {scalar_t__ ht_en; } ;
struct adapter {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  data_sc; int /*<<< orphan*/  data_bw; } ;
typedef  TYPE_1__* PTXDESC_8723B ;

/* Variables and functions */
 int /*<<< orphan*/  BWMapping_8723B (struct adapter*,struct pkt_attrib*) ; 
 int /*<<< orphan*/  SCMapping_8723B (struct adapter*,struct pkt_attrib*) ; 

__attribute__((used)) static void fill_txdesc_phy_8723b(struct adapter *padapter, struct pkt_attrib *pattrib, PTXDESC_8723B ptxdesc)
{
	/* DBG_8192C("bwmode =%d, ch_off =%d\n", pattrib->bwmode, pattrib->ch_offset); */

	if (pattrib->ht_en) {
		ptxdesc->data_bw = BWMapping_8723B(padapter, pattrib);

		ptxdesc->data_sc = SCMapping_8723B(padapter, pattrib);
	}
}