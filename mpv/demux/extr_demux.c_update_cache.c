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
typedef  scalar_t__ uint64_t ;
struct stream {int dummy; } ;
struct mp_tags {int dummy; } ;
struct demuxer {struct stream* stream; } ;
struct demux_internal {scalar_t__ last_speed_query; scalar_t__ cache_unbuffered_read_bytes; int bytes_per_second; int /*<<< orphan*/  lock; scalar_t__ next_cache_update; scalar_t__ stream_size; struct demuxer* d_thread; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/  MP_NOPTS_VALUE ; 
 scalar_t__ MP_SECOND_US ; 
 int /*<<< orphan*/  STREAM_CTRL_GET_METADATA ; 
 int /*<<< orphan*/  add_timed_metadata (struct demux_internal*,struct mp_tags*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_time_us () ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stream_control (struct stream*,int /*<<< orphan*/ ,struct mp_tags**) ; 
 scalar_t__ stream_get_size (struct stream*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_tags*) ; 
 int /*<<< orphan*/  update_bytes_read (struct demux_internal*) ; 

__attribute__((used)) static void update_cache(struct demux_internal *in)
{
    struct demuxer *demuxer = in->d_thread;
    struct stream *stream = demuxer->stream;

    // Don't lock while querying the stream.
    struct mp_tags *stream_metadata = NULL;

    int64_t stream_size = -1;
    if (stream) {
        stream_size = stream_get_size(stream);
        stream_control(stream, STREAM_CTRL_GET_METADATA, &stream_metadata);
    }

    update_bytes_read(in);

    pthread_mutex_lock(&in->lock);

    in->stream_size = stream_size;
    if (stream_metadata) {
        add_timed_metadata(in, stream_metadata, NULL, MP_NOPTS_VALUE);
        talloc_free(stream_metadata);
    }

    in->next_cache_update = INT64_MAX;

    int64_t now = mp_time_us();
    int64_t diff = now - in->last_speed_query;
    if (diff >= MP_SECOND_US) {
        uint64_t bytes = in->cache_unbuffered_read_bytes;
        in->cache_unbuffered_read_bytes = 0;
        in->last_speed_query = now;
        in->bytes_per_second = bytes / (diff / (double)MP_SECOND_US);
    }
    // The idea is to update as long as there is "activity".
    if (in->bytes_per_second)
        in->next_cache_update = now + MP_SECOND_US + 1;

    pthread_mutex_unlock(&in->lock);
}