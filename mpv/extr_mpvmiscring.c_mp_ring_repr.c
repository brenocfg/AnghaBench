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
struct mp_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_ring_available (struct mp_ring*) ; 
 int /*<<< orphan*/  mp_ring_buffered (struct mp_ring*) ; 
 int /*<<< orphan*/  mp_ring_size (struct mp_ring*) ; 
 char* talloc_asprintf (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *mp_ring_repr(struct mp_ring *buffer, void *talloc_ctx)
{
    return talloc_asprintf(
        talloc_ctx,
        "Ringbuffer { .size = %dB, .buffered = %dB, .available = %dB }",
        mp_ring_size(buffer),
        mp_ring_buffered(buffer),
        mp_ring_available(buffer));
}