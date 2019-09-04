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
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  falcon_deconfigure_mac_wrapper (struct ef4_nic*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void falcon_prepare_flush(struct ef4_nic *efx)
{
	falcon_deconfigure_mac_wrapper(efx);

	/* Wait for the tx and rx fifo's to get to the next packet boundary
	 * (~1ms without back-pressure), then to drain the remainder of the
	 * fifo's at data path speeds (negligible), with a healthy margin. */
	msleep(10);
}