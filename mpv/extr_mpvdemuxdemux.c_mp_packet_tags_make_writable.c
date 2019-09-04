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
 int atomic_load (int /*<<< orphan*/ *) ; 
 struct mp_packet_tags* mp_packet_tags_copy (struct mp_packet_tags*) ; 
 int /*<<< orphan*/  mp_packet_tags_unref (struct mp_packet_tags*) ; 

__attribute__((used)) static void mp_packet_tags_make_writable(struct mp_packet_tags **tags)
{
    if (*tags && atomic_load(&(*tags)->refcount) == 1)
        return;
    struct mp_packet_tags *new = mp_packet_tags_copy(*tags);
    mp_packet_tags_unref(*tags);
    *tags = new;
}