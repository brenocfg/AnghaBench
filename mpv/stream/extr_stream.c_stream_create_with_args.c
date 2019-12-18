#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stream_open_args {int flags; int /*<<< orphan*/  url; TYPE_1__* global; int /*<<< orphan*/  cancel; scalar_t__ sinfo; } ;
struct stream {int dummy; } ;
struct mp_log {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int STREAM_NO_MATCH ; 
 int STREAM_OK ; 
 int STREAM_SILENT ; 
 int STREAM_UNSAFE ; 
 int STREAM_UNSUPPORTED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_cancel_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,...) ; 
 struct mp_log* mp_log_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int stream_create_instance (scalar_t__,struct stream_open_args*,struct stream**) ; 
 scalar_t__* stream_list ; 
 int /*<<< orphan*/  talloc_free (struct mp_log*) ; 

int stream_create_with_args(struct stream_open_args *args, struct stream **ret)

{
    assert(args->url);

    int r = STREAM_NO_MATCH;
    *ret = NULL;

    // Open stream proper
    if (args->sinfo) {
        r = stream_create_instance(args->sinfo, args, ret);
    } else {
        for (int i = 0; stream_list[i]; i++) {
            r = stream_create_instance(stream_list[i], args, ret);
            if (r == STREAM_OK)
                break;
            if (r == STREAM_NO_MATCH || r == STREAM_UNSUPPORTED)
                continue;
            if (r == STREAM_UNSAFE)
                continue;
            break;
        }
    }

    if (!*ret && !(args->flags & STREAM_SILENT) && !mp_cancel_test(args->cancel))
    {
        struct mp_log *log = mp_log_new(NULL, args->global->log, "!stream");

        if (r == STREAM_UNSAFE) {
            mp_err(log, "\nRefusing to load potentially unsafe URL from a playlist.\n"
                   "Use --playlist=file or the --load-unsafe-playlists option to "
                   "load it anyway.\n\n");
        } else if (r == STREAM_NO_MATCH || r == STREAM_UNSUPPORTED) {
            mp_err(log, "No protocol handler found to open URL %s\n", args->url);
            mp_err(log, "The protocol is either unsupported, or was disabled "
                        "at compile-time.\n");
        } else {
            mp_err(log, "Failed to open %s.\n", args->url);
        }

        talloc_free(log);
    }

    return r;
}