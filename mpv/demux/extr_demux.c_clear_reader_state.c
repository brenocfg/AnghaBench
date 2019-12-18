#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct demux_internal {int num_streams; int warned_queue_overflow; int blocked; int need_back_seek; TYPE_2__* d_user; TYPE_1__** streams; } ;
struct TYPE_4__ {int filepos; } ;
struct TYPE_3__ {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  ds_clear_reader_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_reader_state(struct demux_internal *in,
                               bool clear_back_state)
{
    for (int n = 0; n < in->num_streams; n++)
        ds_clear_reader_state(in->streams[n]->ds, clear_back_state);
    in->warned_queue_overflow = false;
    in->d_user->filepos = -1; // implicitly synchronized
    in->blocked = false;
    in->need_back_seek = false;
}