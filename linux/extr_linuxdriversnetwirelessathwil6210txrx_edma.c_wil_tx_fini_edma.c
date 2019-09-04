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
struct wil_status_ring {int dummy; } ;
struct wil6210_priv {size_t tx_sring_idx; struct wil_status_ring* srings; } ;

/* Variables and functions */
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_sring_free (struct wil6210_priv*,struct wil_status_ring*) ; 

__attribute__((used)) static void wil_tx_fini_edma(struct wil6210_priv *wil)
{
	struct wil_status_ring *sring = &wil->srings[wil->tx_sring_idx];

	wil_dbg_misc(wil, "free TX sring\n");

	wil_sring_free(wil, sring);
}