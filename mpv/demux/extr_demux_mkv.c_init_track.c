#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sh_stream {int /*<<< orphan*/  forced_track; int /*<<< orphan*/  default_track; int /*<<< orphan*/  title; int /*<<< orphan*/  demuxer_id; scalar_t__ lang; } ;
struct TYPE_3__ {int /*<<< orphan*/  forced_track; int /*<<< orphan*/  default_track; int /*<<< orphan*/  name; int /*<<< orphan*/  tnum; scalar_t__ language; struct sh_stream* stream; } ;
typedef  TYPE_1__ mkv_track_t ;
typedef  int /*<<< orphan*/  demuxer_t ;

/* Variables and functions */
 scalar_t__ strcmp (scalar_t__,char*) ; 

__attribute__((used)) static void init_track(demuxer_t *demuxer, mkv_track_t *track,
                       struct sh_stream *sh)
{
    track->stream = sh;

    if (track->language && (strcmp(track->language, "und") != 0))
        sh->lang = track->language;

    sh->demuxer_id = track->tnum;
    sh->title = track->name;
    sh->default_track = track->default_track;
    sh->forced_track = track->forced_track;
}