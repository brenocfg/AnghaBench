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
struct br2684_vcc {int /*<<< orphan*/  (* old_release_cb ) (struct atm_vcc*) ;int /*<<< orphan*/  device; int /*<<< orphan*/  qspace; } ;
struct atm_vcc {int dummy; } ;

/* Variables and functions */
 struct br2684_vcc* BR2684_VCC (struct atm_vcc*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct atm_vcc*) ; 

__attribute__((used)) static void br2684_release_cb(struct atm_vcc *atmvcc)
{
	struct br2684_vcc *brvcc = BR2684_VCC(atmvcc);

	if (atomic_read(&brvcc->qspace) > 0)
		netif_wake_queue(brvcc->device);

	if (brvcc->old_release_cb)
		brvcc->old_release_cb(atmvcc);
}