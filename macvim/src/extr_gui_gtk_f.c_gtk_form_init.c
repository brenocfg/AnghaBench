#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int width; int height; scalar_t__ freeze_count; int /*<<< orphan*/  visibility; scalar_t__ configure_serial; int /*<<< orphan*/ * bin_window; int /*<<< orphan*/ * children; } ;
typedef  TYPE_1__ GtkForm ;

/* Variables and functions */
 int /*<<< orphan*/  GDK_VISIBILITY_PARTIAL ; 

__attribute__((used)) static void
gtk_form_init(GtkForm *form)
{
    form->children = NULL;

    form->width = 1;
    form->height = 1;

    form->bin_window = NULL;

    form->configure_serial = 0;
    form->visibility = GDK_VISIBILITY_PARTIAL;

    form->freeze_count = 0;
}