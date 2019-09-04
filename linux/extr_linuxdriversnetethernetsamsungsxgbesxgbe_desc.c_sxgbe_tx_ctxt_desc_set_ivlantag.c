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
struct sxgbe_tx_ctxt_desc {int ivlan_tag_valid; int ivlan_tag; int ivlan_tag_ctl; } ;

/* Variables and functions */

__attribute__((used)) static void sxgbe_tx_ctxt_desc_set_ivlantag(struct sxgbe_tx_ctxt_desc *p,
					    int is_ivlanvalid, int ivlan_tag,
					    int ivlan_ctl)
{
	if (is_ivlanvalid) {
		p->ivlan_tag_valid = is_ivlanvalid;
		p->ivlan_tag = ivlan_tag;
		p->ivlan_tag_ctl = ivlan_ctl;
	}
}