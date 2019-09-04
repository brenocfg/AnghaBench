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
struct libipw_device {int /*<<< orphan*/ * networks; } ;

/* Variables and functions */
 int MAX_NETWORK_COUNT ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void libipw_networks_free(struct libipw_device *ieee)
{
	int i;

	for (i = 0; i < MAX_NETWORK_COUNT; i++)
		kfree(ieee->networks[i]);
}