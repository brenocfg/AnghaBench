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
struct netdev {scalar_t__ filename_speed; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  freez (void*) ; 
 int /*<<< orphan*/  netdev_added ; 
 int /*<<< orphan*/  netdev_charts_release (struct netdev*) ; 
 int /*<<< orphan*/  netdev_free_chart_strings (struct netdev*) ; 

__attribute__((used)) static void netdev_free(struct netdev *d) {
    netdev_charts_release(d);
    netdev_free_chart_strings(d);

    freez((void *)d->name);
    freez((void *)d->filename_speed);
    freez((void *)d);
    netdev_added--;
}