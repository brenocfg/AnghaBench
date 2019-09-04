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
struct mp_refqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_refqueue_has_output (struct mp_refqueue*) ; 
 int /*<<< orphan*/  mp_refqueue_next (struct mp_refqueue*) ; 
 int /*<<< orphan*/  output_next_field (struct mp_refqueue*) ; 

__attribute__((used)) static void mp_refqueue_next_field(struct mp_refqueue *q)
{
    if (!mp_refqueue_has_output(q))
        return;

    if (!output_next_field(q))
        mp_refqueue_next(q);
}