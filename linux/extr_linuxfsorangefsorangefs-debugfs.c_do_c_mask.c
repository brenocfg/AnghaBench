#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct client_debug_mask {int mask1; int mask2; } ;
struct TYPE_2__ {int mask1; int mask2; int /*<<< orphan*/  keyword; } ;

/* Variables and functions */
 TYPE_1__* cdm_array ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void do_c_mask(int i, char *unchecked_keyword,
    struct client_debug_mask **sane_mask)
{

	if (!strcmp(cdm_array[i].keyword, unchecked_keyword)) {
		(**sane_mask).mask1 = (**sane_mask).mask1 | cdm_array[i].mask1;
		(**sane_mask).mask2 = (**sane_mask).mask2 | cdm_array[i].mask2;
	}
}