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
struct stream {int dummy; } ;
struct demuxer {struct stream* stream; struct demux_internal* in; } ;
struct demux_internal {int /*<<< orphan*/  stream_base_filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_CTRL_GET_BASE_FILENAME ; 
 int /*<<< orphan*/  stream_control (struct stream*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  talloc_steal (struct demuxer*,char*) ; 

__attribute__((used)) static void demux_init_cache(struct demuxer *demuxer)
{
    struct demux_internal *in = demuxer->in;
    struct stream *stream = demuxer->stream;

    char *base = NULL;
    stream_control(stream, STREAM_CTRL_GET_BASE_FILENAME, &base);
    in->stream_base_filename = talloc_steal(demuxer, base);
}