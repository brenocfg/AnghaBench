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
struct mtu3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtu3_device_disable (struct mtu3*) ; 
 int /*<<< orphan*/  mtu3_mem_free (struct mtu3*) ; 

__attribute__((used)) static void mtu3_hw_exit(struct mtu3 *mtu)
{
	mtu3_device_disable(mtu);
	mtu3_mem_free(mtu);
}