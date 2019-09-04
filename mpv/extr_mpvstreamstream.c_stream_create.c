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
struct mpv_global {int /*<<< orphan*/  log; } ;
struct mp_log {int dummy; } ;
struct mp_cancel {int dummy; } ;

/* Variables and functions */
 int INT_MAX ; 
 int STREAM_NO_MATCH ; 
 int STREAM_OK ; 
 int STREAM_UNSAFE ; 
 int STREAM_UNSUPPORTED ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  mp_cancel_test (struct mp_cancel*) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,...) ; 
 struct mp_log* mp_log_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int open_internal (scalar_t__,char const*,int,struct mp_cancel*,struct mpv_global*,struct stream**) ; 
 scalar_t__* stream_list ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_log*) ; 

struct stream *stream_create(const char *url, int flags,
                             struct mp_cancel *c, struct mpv_global *global)
{
    struct mp_log *log = mp_log_new(NULL, global->log, "!stream");
    struct stream *s = NULL;
    assert(url);

    if (strlen(url) > INT_MAX / 8)
        goto done;

    // Open stream proper
    bool unsafe = false;
    for (int i = 0; stream_list[i]; i++) {
        int r = open_internal(stream_list[i], url, flags, c, global, &s);
        if (r == STREAM_OK)
            break;
        if (r == STREAM_NO_MATCH || r == STREAM_UNSUPPORTED)
            continue;
        if (r == STREAM_UNSAFE) {
            unsafe = true;
            continue;
        }
        if (r != STREAM_OK) {
            if (!mp_cancel_test(c))
                mp_err(log, "Failed to open %s.\n", url);
            goto done;
        }
    }

    if (!s && unsafe) {
        mp_err(log, "\nRefusing to load potentially unsafe URL from a playlist.\n"
               "Use --playlist=file or the --load-unsafe-playlists option to "
               "load it anyway.\n\n");
        goto done;
    }

    if (!s) {
        mp_err(log, "No protocol handler found to open URL %s\n", url);
        mp_err(log, "The protocol is either unsupported, or was disabled "
                    "at compile-time.\n");
        goto done;
    }

done:
    talloc_free(log);
    return s;
}