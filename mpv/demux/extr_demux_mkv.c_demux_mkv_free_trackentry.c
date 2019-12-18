#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* parser_tmp; } ;
typedef  TYPE_1__ mkv_track_t ;

/* Variables and functions */
 int /*<<< orphan*/  talloc_free (TYPE_1__*) ; 

__attribute__((used)) static void demux_mkv_free_trackentry(mkv_track_t *track)
{
    talloc_free(track->parser_tmp);
    talloc_free(track);
}