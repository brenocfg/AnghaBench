#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct demuxer {TYPE_1__* in; } ;
struct TYPE_2__ {int autoselect; int /*<<< orphan*/  threading; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void demux_set_stream_autoselect(struct demuxer *demuxer, bool autoselect)
{
    assert(!demuxer->in->threading); // laziness
    demuxer->in->autoselect = autoselect;
}