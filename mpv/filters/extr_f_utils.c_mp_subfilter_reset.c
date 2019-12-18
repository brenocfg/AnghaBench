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
struct mp_subfilter {int draining; int /*<<< orphan*/  frame; scalar_t__ filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  TA_FREEP (scalar_t__*) ; 
 int /*<<< orphan*/  mp_frame_unref (int /*<<< orphan*/ *) ; 

void mp_subfilter_reset(struct mp_subfilter *sub)
{
    if (sub->filter && sub->draining)
        TA_FREEP(&sub->filter);
    sub->draining = false;
    mp_frame_unref(&sub->frame);
}