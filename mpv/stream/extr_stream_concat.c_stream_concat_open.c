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
struct stream_open_args {char* url; int flags; struct priv* special_arg; int /*<<< orphan*/ * sinfo; struct mp_cancel* cancel; struct mpv_global* global; } ;
struct stream {int dummy; } ;
struct priv {int num_streams; struct stream** streams; } ;
struct mpv_global {int dummy; } ;
struct mp_cancel {int dummy; } ;

/* Variables and functions */
 int STREAM_READ ; 
 int STREAM_SILENT ; 
 int /*<<< orphan*/  stream_create_with_args (struct stream_open_args*,struct stream**) ; 
 int /*<<< orphan*/  stream_info_concat ; 

struct stream *stream_concat_open(struct mpv_global *global, struct mp_cancel *c,
                                  struct stream **streams, int num_streams)
{
    // (struct priv is blatantly abused to pass in the stream list)
    struct priv arg = {
        .streams = streams,
        .num_streams = num_streams,
    };

    struct stream_open_args sargs = {
        .global = global,
        .cancel = c,
        .url = "concat://",
        .flags = STREAM_READ | STREAM_SILENT,
        .sinfo = &stream_info_concat,
        .special_arg = &arg,
    };

    struct stream *s = NULL;
    stream_create_with_args(&sargs, &s);
    return s;
}