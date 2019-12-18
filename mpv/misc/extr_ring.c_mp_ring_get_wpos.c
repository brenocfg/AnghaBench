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
struct mp_ring {int /*<<< orphan*/  wpos; } ;

/* Variables and functions */
 unsigned long long atomic_load (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long long mp_ring_get_wpos(struct mp_ring *buffer)
{
    return atomic_load(&buffer->wpos);
}