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
struct wilc_vif {int dummy; } ;
struct wilc {struct wilc_vif** vif; } ;

/* Variables and functions */
 int NUM_CONCURRENT_IFC ; 

__attribute__((used)) static struct wilc_vif *wilc_get_vif_from_idx(struct wilc *wilc, int idx)
{
	int index = idx - 1;

	if (index < 0 || index >= NUM_CONCURRENT_IFC)
		return NULL;

	return wilc->vif[index];
}