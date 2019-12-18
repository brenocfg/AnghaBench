#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct stream_avseek {int /*<<< orphan*/  flags; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  stream_index; } ;
struct mp_tags {int dummy; } ;
struct TYPE_11__ {TYPE_3__* priv; } ;
typedef  TYPE_2__ stream_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_13__ {char* (* item_name ) (void*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  read_seek; TYPE_1__* av_class; } ;
struct TYPE_10__ {void* (* child_next ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ AVIOContext ;
typedef  TYPE_4__ AVClass ;

/* Variables and functions */
#define  STREAM_CTRL_AVSEEK 130 
#define  STREAM_CTRL_GET_METADATA 129 
#define  STREAM_CTRL_HAS_AVSEEK 128 
 int STREAM_UNSUPPORTED ; 
 int /*<<< orphan*/  avio_seek_time (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mp_tags* read_icy (TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const* const) ; 
 int /*<<< orphan*/  stream_drop_buffers (TYPE_2__*) ; 
 void* stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 
 char* stub2 (void*) ; 

__attribute__((used)) static int control(stream_t *s, int cmd, void *arg)
{
    AVIOContext *avio = s->priv;
    switch(cmd) {
    case STREAM_CTRL_AVSEEK: {
        struct stream_avseek *c = arg;
        int64_t r = avio_seek_time(avio, c->stream_index, c->timestamp, c->flags);
        if (r >= 0) {
            stream_drop_buffers(s);
            return 1;
        }
        break;
    }
    case STREAM_CTRL_HAS_AVSEEK: {
        // Starting at some point, read_seek is always available, and runtime
        // behavior decides whether it exists or not. FFmpeg's API doesn't
        // return anything helpful to determine seekability upfront, so here's
        // a hardcoded whitelist. Not our fault.
        // In addition we also have to jump through ridiculous hoops just to
        // get the fucking protocol name.
        const char *proto = NULL;
        if (avio->av_class && avio->av_class->child_next) {
            // This usually yields the URLContext (why does it even exist?),
            // which holds the name of the actual protocol implementation.
            void *child = avio->av_class->child_next(avio, NULL);
            AVClass *cl = *(AVClass **)child;
            if (cl && cl->item_name)
                proto = cl->item_name(child);
        }
        static const char *const has_read_seek[] = {
            "rtmp", "rtmpt", "rtmpe", "rtmpte", "rtmps", "rtmpts", "mmsh", 0};
        for (int n = 0; has_read_seek[n]; n++) {
            if (avio->read_seek && proto && strcmp(proto, has_read_seek[n]) == 0)
                return 1;
        }
        break;
    }
    case STREAM_CTRL_GET_METADATA: {
        *(struct mp_tags **)arg = read_icy(s);
        if (!*(struct mp_tags **)arg)
            break;
        return 1;
    }
    }
    return STREAM_UNSUPPORTED;
}