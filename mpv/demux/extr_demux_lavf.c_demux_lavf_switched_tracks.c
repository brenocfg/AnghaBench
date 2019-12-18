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
 int /*<<< orphan*/  select_tracks (struct demuxer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void demux_lavf_switched_tracks(struct demuxer *demuxer)
{
    select_tracks(demuxer, 0);
}