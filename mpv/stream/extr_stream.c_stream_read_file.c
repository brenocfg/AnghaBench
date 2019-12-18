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
struct mpv_global {int dummy; } ;
struct bstr {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_stream (int /*<<< orphan*/ *) ; 
 char* mp_get_user_path (int /*<<< orphan*/ *,struct mpv_global*,char const*) ; 
 int /*<<< orphan*/ * stream_open (char*,struct mpv_global*) ; 
 struct bstr stream_read_complete (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

struct bstr stream_read_file(const char *filename, void *talloc_ctx,
                             struct mpv_global *global, int max_size)
{
    struct bstr res = {0};
    char *fname = mp_get_user_path(NULL, global, filename);
    stream_t *s = stream_open(fname, global);
    if (s) {
        res = stream_read_complete(s, talloc_ctx, max_size);
        free_stream(s);
    }
    talloc_free(fname);
    return res;
}