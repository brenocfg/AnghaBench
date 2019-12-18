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
struct demux_internal {int back_demuxing; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct demux_internal*,char*) ; 
 int /*<<< orphan*/  clear_reader_state (struct demux_internal*,int) ; 

__attribute__((used)) static void error_on_backward_demuxing(struct demux_internal *in)
{
    if (!in->back_demuxing)
        return;
    MP_ERR(in, "Disabling backward demuxing.\n");
    in->back_demuxing = false;
    clear_reader_state(in, true);
}