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
struct demux_internal {int /*<<< orphan*/  slave_unbuffered_read_bytes; struct demuxer* d_thread; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void demux_report_unbuffered_read_bytes(struct demuxer *demuxer, int64_t new)
{
    struct demux_internal *in = demuxer->in;
    assert(demuxer == in->d_thread);

    in->slave_unbuffered_read_bytes += new;
}