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
typedef  int uint32_t ;
struct demuxer {int /*<<< orphan*/  stream; int /*<<< orphan*/  log; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int EBML_ID_INVALID ; 
#define  MATROSKA_ID_ATTACHMENTS 134 
#define  MATROSKA_ID_CHAPTERS 133 
#define  MATROSKA_ID_CUES 132 
#define  MATROSKA_ID_INFO 131 
#define  MATROSKA_ID_SEEKHEAD 130 
#define  MATROSKA_ID_TAGS 129 
#define  MATROSKA_ID_TRACKS 128 
 int demux_mkv_read_attachments (struct demuxer*) ; 
 int demux_mkv_read_chapters (struct demuxer*) ; 
 int demux_mkv_read_cues (struct demuxer*) ; 
 int demux_mkv_read_info (struct demuxer*) ; 
 int demux_mkv_read_seekhead (struct demuxer*) ; 
 int demux_mkv_read_tags (struct demuxer*) ; 
 int demux_mkv_read_tracks (struct demuxer*) ; 
 int /*<<< orphan*/  ebml_read_skip (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_header_element (struct demuxer*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_header_element(struct demuxer *demuxer, uint32_t id,
                               int64_t start_filepos)
{
    if (id == EBML_ID_INVALID)
        return 0;

    if (test_header_element(demuxer, id, start_filepos))
        goto skip;

    switch(id) {
    case MATROSKA_ID_INFO:
        return demux_mkv_read_info(demuxer);
    case MATROSKA_ID_TRACKS:
        return demux_mkv_read_tracks(demuxer);
    case MATROSKA_ID_CUES:
        return demux_mkv_read_cues(demuxer);
    case MATROSKA_ID_TAGS:
        return demux_mkv_read_tags(demuxer);
    case MATROSKA_ID_SEEKHEAD:
        return demux_mkv_read_seekhead(demuxer);
    case MATROSKA_ID_CHAPTERS:
        return demux_mkv_read_chapters(demuxer);
    case MATROSKA_ID_ATTACHMENTS:
        return demux_mkv_read_attachments(demuxer);
    }
skip:
    ebml_read_skip(demuxer->log, -1, demuxer->stream);
    return 0;
}