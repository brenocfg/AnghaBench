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
struct mp_packet_tags {struct mp_packet_tags* stream; struct mp_packet_tags* demux; struct mp_packet_tags* sh; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int atomic_fetch_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  talloc_free (struct mp_packet_tags*) ; 

void mp_packet_tags_unref(struct mp_packet_tags *tags)
{
    if (tags) {
        if (atomic_fetch_add(&tags->refcount, -1) == 1) {
            talloc_free(tags->sh);
            talloc_free(tags->demux);
            talloc_free(tags->stream);
            talloc_free(tags);
        }
    }
}