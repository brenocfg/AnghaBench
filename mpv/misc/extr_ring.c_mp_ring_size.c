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
struct mp_ring {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int talloc_get_size (int /*<<< orphan*/ ) ; 

int mp_ring_size(struct mp_ring *buffer)
{
    return talloc_get_size(buffer->buffer);
}