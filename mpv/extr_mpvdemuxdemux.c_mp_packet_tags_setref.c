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
struct mp_packet_tags {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_fetch_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_packet_tags_unref (struct mp_packet_tags*) ; 

void mp_packet_tags_setref(struct mp_packet_tags **dst, struct mp_packet_tags *src)
{
    if (src)
        atomic_fetch_add(&src->refcount, 1);
    mp_packet_tags_unref(*dst);
    *dst = src;
}