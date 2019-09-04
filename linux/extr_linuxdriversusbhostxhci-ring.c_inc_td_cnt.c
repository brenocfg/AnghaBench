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
struct urb_priv {int /*<<< orphan*/  num_tds_done; } ;
struct urb {struct urb_priv* hcpriv; } ;

/* Variables and functions */

__attribute__((used)) static void inc_td_cnt(struct urb *urb)
{
	struct urb_priv *urb_priv = urb->hcpriv;

	urb_priv->num_tds_done++;
}