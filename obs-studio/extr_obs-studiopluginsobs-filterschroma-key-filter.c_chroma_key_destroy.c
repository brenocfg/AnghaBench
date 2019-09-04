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
struct chroma_key_filter_data {scalar_t__ effect; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (void*) ; 
 int /*<<< orphan*/  gs_effect_destroy (scalar_t__) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 

__attribute__((used)) static void chroma_key_destroy(void *data)
{
	struct chroma_key_filter_data *filter = data;

	if (filter->effect) {
		obs_enter_graphics();
		gs_effect_destroy(filter->effect);
		obs_leave_graphics();
	}

	bfree(data);
}