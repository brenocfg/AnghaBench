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
struct demuxer {int dummy; } ;

/* Variables and functions */
 int CONTROL_OK ; 
 int CONTROL_UNKNOWN ; 
 int DEMUXER_CTRL_SWITCHED_TRACKS ; 
 int /*<<< orphan*/  reselect_streams (struct demuxer*) ; 

__attribute__((used)) static int d_control(struct demuxer *demuxer, int cmd, void *arg)
{
    if (cmd == DEMUXER_CTRL_SWITCHED_TRACKS) {
        reselect_streams(demuxer);
        return CONTROL_OK;
    }

    return CONTROL_UNKNOWN;
}