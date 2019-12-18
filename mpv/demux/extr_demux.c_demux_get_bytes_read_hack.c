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
struct demuxer {struct demux_internal* in; } ;
struct demux_internal {scalar_t__ hack_unbuffered_read_bytes; int /*<<< orphan*/  threading; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  update_bytes_read (struct demux_internal*) ; 

int64_t demux_get_bytes_read_hack(struct demuxer *demuxer)
{
    struct demux_internal *in = demuxer->in;

    // Required because demuxer==in->d_user, and we access in->d_thread.
    // Locking won't solve this, because we also need to access struct stream.
    assert(!in->threading);

    update_bytes_read(in);

    int64_t res = in->hack_unbuffered_read_bytes;
    in->hack_unbuffered_read_bytes = 0;
    return res;
}