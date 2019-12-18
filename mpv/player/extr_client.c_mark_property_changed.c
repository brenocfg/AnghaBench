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
struct observe_property {int changed; int async_change_ts; } ;
struct mpv_handle {int /*<<< orphan*/  lowest_changed; struct observe_property** properties; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPMIN (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mark_property_changed(struct mpv_handle *client, int index)
{
    struct observe_property *prop = client->properties[index];
    prop->changed = true;
    prop->async_change_ts += 1;
    client->lowest_changed = MPMIN(client->lowest_changed, index);
}