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
struct vo_w32_state {scalar_t__ monitor; } ;

/* Variables and functions */
 int /*<<< orphan*/  update_display_info (struct vo_w32_state*) ; 

__attribute__((used)) static void force_update_display_info(struct vo_w32_state *w32)
{
    w32->monitor = 0;
    update_display_info(w32);
}