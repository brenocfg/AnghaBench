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
struct gs_init_data {int /*<<< orphan*/  zsformat; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_RGBA ; 
 int /*<<< orphan*/  GS_ZS_NONE ; 

__attribute__((used)) static void init_dummy_swap_info(struct gs_init_data *info)
{
	info->format = GS_RGBA;
	info->zsformat = GS_ZS_NONE;
}