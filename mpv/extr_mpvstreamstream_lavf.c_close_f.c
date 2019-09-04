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
struct TYPE_3__ {int /*<<< orphan*/ * priv; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_f(stream_t *stream)
{
    AVIOContext *avio = stream->priv;
    /* NOTE: As of 2011 write streams must be manually flushed before close.
     * Currently write_buffer() always flushes them after writing.
     * avio_close() could return an error, but we have no way to return that
     * with the current stream API.
     */
    if (avio)
        avio_close(avio);
}