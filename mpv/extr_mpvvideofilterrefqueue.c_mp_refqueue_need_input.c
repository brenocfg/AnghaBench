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
struct mp_refqueue {scalar_t__ pos; scalar_t__ needed_future_frames; int /*<<< orphan*/  eof; } ;

/* Variables and functions */

__attribute__((used)) static bool mp_refqueue_need_input(struct mp_refqueue *q)
{
    return q->pos < q->needed_future_frames && !q->eof;
}