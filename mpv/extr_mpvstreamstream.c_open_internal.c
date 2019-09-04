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
struct stream {int mode; int access_references; int read_chunk; int sector_size; int seekable; char const* mime_type; int /*<<< orphan*/  seek; scalar_t__ is_network; void* path; void* url; struct mpv_global* global; struct mp_cancel* cancel; TYPE_1__ const* info; int /*<<< orphan*/  log; } ;
struct mpv_global {scalar_t__ config; int /*<<< orphan*/  log; } ;
struct mp_cancel {int dummy; } ;
typedef  struct stream stream_t ;
struct TYPE_3__ {int (* open ) (struct stream*) ;int /*<<< orphan*/  can_write; scalar_t__ is_network; int /*<<< orphan*/  name; scalar_t__* protocols; int /*<<< orphan*/  is_safe; } ;
typedef  TYPE_1__ stream_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_DBG (struct stream*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct stream*,char*,char const*) ; 
 int STREAM_BUFFER_SIZE ; 
 int STREAM_NETWORK_ONLY ; 
 int STREAM_NO_MATCH ; 
 int STREAM_OK ; 
 int STREAM_READ ; 
 int STREAM_SAFE_ONLY ; 
 int STREAM_UNSAFE ; 
 int STREAM_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  m_option_type_flag ; 
 char* match_proto (char const*,scalar_t__) ; 
 int /*<<< orphan*/  mp_log_new (struct stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_read_option_raw (struct mpv_global*,char*,int /*<<< orphan*/ *,int*) ; 
 struct stream* new_stream () ; 
 int stub1 (struct stream*) ; 
 int /*<<< orphan*/  talloc_free (struct stream*) ; 
 void* talloc_strdup (struct stream*,char const*) ; 

__attribute__((used)) static int open_internal(const stream_info_t *sinfo, const char *url, int flags,
                         struct mp_cancel *c, struct mpv_global *global,
                         struct stream **ret)
{
    if (!sinfo->is_safe && (flags & STREAM_SAFE_ONLY))
        return STREAM_UNSAFE;
    if (!sinfo->is_network && (flags & STREAM_NETWORK_ONLY))
        return STREAM_UNSAFE;

    const char *path = url;
    for (int n = 0; sinfo->protocols && sinfo->protocols[n]; n++) {
        path = match_proto(url, sinfo->protocols[n]);
        if (path)
            break;
    }

    if (!path)
        return STREAM_NO_MATCH;

    stream_t *s = new_stream();
    s->log = mp_log_new(s, global->log, sinfo->name);
    s->info = sinfo;
    s->cancel = c;
    s->global = global;
    s->url = talloc_strdup(s, url);
    s->path = talloc_strdup(s, path);
    s->is_network = sinfo->is_network;
    s->mode = flags & (STREAM_READ | STREAM_WRITE);

    if (global->config) {
        int opt;
        mp_read_option_raw(global, "access-references", &m_option_type_flag, &opt);
        s->access_references = opt;
    }

    MP_VERBOSE(s, "Opening %s\n", url);

    if ((s->mode & STREAM_WRITE) && !sinfo->can_write) {
        MP_DBG(s, "No write access implemented.\n");
        talloc_free(s);
        return STREAM_NO_MATCH;
    }

    int r = (sinfo->open)(s);
    if (r != STREAM_OK) {
        talloc_free(s);
        return r;
    }

    if (!s->read_chunk)
        s->read_chunk = 4 * (s->sector_size ? s->sector_size : STREAM_BUFFER_SIZE);

    assert(s->seekable == !!s->seek);

    if (s->mime_type)
        MP_VERBOSE(s, "Mime-type: '%s'\n", s->mime_type);

    MP_DBG(s, "Stream opened successfully.\n");

    *ret = s;
    return STREAM_OK;
}