#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct playlist_entry {int /*<<< orphan*/  title; } ;
struct pl_parser {scalar_t__ check_level; char* format; int /*<<< orphan*/  pl; scalar_t__ probing; TYPE_2__* real_stream; } ;
typedef  int /*<<< orphan*/  probe ;
struct TYPE_12__ {char* member_0; int member_1; int len; } ;
typedef  TYPE_1__ bstr ;
struct TYPE_13__ {int /*<<< orphan*/  url; } ;

/* Variables and functions */
 scalar_t__ DEMUX_CHECK_UNSAFE ; 
 int PROBE_SIZE ; 
 scalar_t__ bstr_eatstart0 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  bstr_equals0 (TYPE_1__,char*) ; 
 scalar_t__ bstr_split_tok (TYPE_1__,char*,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ bstr_startswith0 (TYPE_1__,char*) ; 
 TYPE_1__ bstr_strip (int /*<<< orphan*/ ) ; 
 char* bstrto0 (int /*<<< orphan*/ *,TYPE_1__) ; 
 scalar_t__ maybe_text (TYPE_1__) ; 
 char* mp_splitext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pl_eof (struct pl_parser*) ; 
 int /*<<< orphan*/  pl_get_line (struct pl_parser*) ; 
 int /*<<< orphan*/  playlist_add (int /*<<< orphan*/ ,struct playlist_entry*) ; 
 struct playlist_entry* playlist_entry_new (char*) ; 
 scalar_t__ strcasecmp (char*,char const*) ; 
 int stream_read_peek (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 int /*<<< orphan*/  talloc_steal (struct playlist_entry*,char*) ; 

__attribute__((used)) static int parse_m3u(struct pl_parser *p)
{
    bstr line = bstr_strip(pl_get_line(p));
    if (p->probing && !bstr_equals0(line, "#EXTM3U")) {
        // Last resort: if the file extension is m3u, it might be headerless.
        if (p->check_level == DEMUX_CHECK_UNSAFE) {
            char *ext = mp_splitext(p->real_stream->url, NULL);
            char probe[PROBE_SIZE];
            int len = stream_read_peek(p->real_stream, probe, sizeof(probe));
            bstr data = {probe, len};
            if (ext && data.len > 10 && maybe_text(data)) {
                const char *exts[] = {"m3u", "m3u8", NULL};
                for (int n = 0; exts[n]; n++) {
                    if (strcasecmp(ext, exts[n]) == 0)
                        goto ok;
                }
            }
        }
        return -1;
    }

ok:
    if (p->probing)
        return 0;

    char *title = NULL;
    while (line.len || !pl_eof(p)) {
        if (bstr_eatstart0(&line, "#EXTINF:")) {
            bstr duration, btitle;
            if (bstr_split_tok(line, ",", &duration, &btitle) && btitle.len) {
                talloc_free(title);
                title = bstrto0(NULL, btitle);
            }
        } else if (bstr_startswith0(line, "#EXT-X-")) {
            p->format = "hls";
        } else if (line.len > 0 && !bstr_startswith0(line, "#")) {
            char *fn = bstrto0(NULL, line);
            struct playlist_entry *e = playlist_entry_new(fn);
            talloc_free(fn);
            e->title = talloc_steal(e, title);
            title = NULL;
            playlist_add(p->pl, e);
        }
        line = bstr_strip(pl_get_line(p));
    }
    talloc_free(title);
    return 0;
}