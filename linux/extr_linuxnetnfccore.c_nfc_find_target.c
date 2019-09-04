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
typedef  scalar_t__ u32 ;
struct nfc_target {scalar_t__ idx; } ;
struct nfc_dev {int n_targets; struct nfc_target* targets; } ;

/* Variables and functions */

__attribute__((used)) static struct nfc_target *nfc_find_target(struct nfc_dev *dev, u32 target_idx)
{
	int i;

	for (i = 0; i < dev->n_targets; i++) {
		if (dev->targets[i].idx == target_idx)
			return &dev->targets[i];
	}

	return NULL;
}