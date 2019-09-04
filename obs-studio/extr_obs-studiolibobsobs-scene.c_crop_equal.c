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
struct obs_sceneitem_crop {scalar_t__ left; scalar_t__ right; scalar_t__ top; scalar_t__ bottom; } ;

/* Variables and functions */

__attribute__((used)) static inline bool crop_equal(const struct obs_sceneitem_crop *crop1,
		const struct obs_sceneitem_crop *crop2)
{
	return crop1->left   == crop2->left  &&
	       crop1->right  == crop2->right &&
	       crop1->top    == crop2->top   &&
	       crop1->bottom == crop2->bottom;
}