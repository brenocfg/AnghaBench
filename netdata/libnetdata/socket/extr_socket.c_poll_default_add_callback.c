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
typedef  int /*<<< orphan*/  POLLINFO ;

/* Variables and functions */

void *poll_default_add_callback(POLLINFO *pi, short int *events, void *data) {
    (void)pi;
    (void)events;
    (void)data;

    // error("POLLFD: internal error: poll_default_add_callback() called");

    return NULL;
}