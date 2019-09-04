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

/* Variables and functions */
 int /*<<< orphan*/  UI_destroy_method (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ui_method ; 

void destroy_ui_method(void)
{
    if (ui_method) {
        UI_destroy_method(ui_method);
        ui_method = NULL;
    }
}