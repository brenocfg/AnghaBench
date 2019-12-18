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
 int mp_ring_get_rpos (struct mp_ring*) ; 
 int mp_ring_get_wpos (struct mp_ring*) ; 

int mp_ring_buffered(struct mp_ring *buffer)
{
    return (mp_ring_get_wpos(buffer) - mp_ring_get_rpos(buffer));
}