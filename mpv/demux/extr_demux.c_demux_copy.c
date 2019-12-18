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
struct demuxer {int /*<<< orphan*/  metadata; int /*<<< orphan*/  priv; int /*<<< orphan*/  is_streaming; int /*<<< orphan*/  is_network; int /*<<< orphan*/  duration; int /*<<< orphan*/  start_time; int /*<<< orphan*/  fully_read; int /*<<< orphan*/  ts_resets_possible; int /*<<< orphan*/  filetype; int /*<<< orphan*/  partially_seekable; int /*<<< orphan*/  seekable; int /*<<< orphan*/  playlist; int /*<<< orphan*/  matroska_data; int /*<<< orphan*/  num_attachments; int /*<<< orphan*/  attachments; int /*<<< orphan*/  edition; int /*<<< orphan*/  num_editions; int /*<<< orphan*/  editions; int /*<<< orphan*/  num_chapters; int /*<<< orphan*/  chapters; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_tags_dup (struct demuxer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void demux_copy(struct demuxer *dst, struct demuxer *src)
{
    // Note that we do as shallow copies as possible. We expect the data
    // that is not-copied (only referenced) to be immutable.
    // This implies e.g. that no chapters are added after initialization.
    dst->chapters = src->chapters;
    dst->num_chapters = src->num_chapters;
    dst->editions = src->editions;
    dst->num_editions = src->num_editions;
    dst->edition = src->edition;
    dst->attachments = src->attachments;
    dst->num_attachments = src->num_attachments;
    dst->matroska_data = src->matroska_data;
    dst->playlist = src->playlist;
    dst->seekable = src->seekable;
    dst->partially_seekable = src->partially_seekable;
    dst->filetype = src->filetype;
    dst->ts_resets_possible = src->ts_resets_possible;
    dst->fully_read = src->fully_read;
    dst->start_time = src->start_time;
    dst->duration = src->duration;
    dst->is_network = src->is_network;
    dst->is_streaming = src->is_streaming;
    dst->priv = src->priv;
    dst->metadata = mp_tags_dup(dst, src->metadata);
}