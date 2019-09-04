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
struct priv {int frame_size; int frame_rate; } ;
struct demuxer {int duration; struct priv* priv; struct stream* stream; } ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_CTRL_GET_SIZE ; 
 scalar_t__ STREAM_OK ; 
 scalar_t__ stream_control (struct stream*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int generic_open(struct demuxer *demuxer)
{
    struct stream *s = demuxer->stream;
    struct priv *p = demuxer->priv;

    int64_t end = 0;
    if (stream_control(s, STREAM_CTRL_GET_SIZE, &end) == STREAM_OK)
        demuxer->duration = (end / p->frame_size) / p->frame_rate;

    return 0;
}