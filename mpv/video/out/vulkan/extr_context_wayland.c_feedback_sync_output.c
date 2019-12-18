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
struct wp_presentation_feedback {int dummy; } ;
struct wl_output {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void feedback_sync_output(void *data, struct wp_presentation_feedback *fback,
                               struct wl_output *output)
{
}