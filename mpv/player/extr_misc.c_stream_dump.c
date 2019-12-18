#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
struct MPOpts {int /*<<< orphan*/  quiet; int /*<<< orphan*/  stream_dump; } ;
struct MPContext {scalar_t__ stop_play; int /*<<< orphan*/  global; struct MPOpts* opts; } ;
struct TYPE_6__ {int pos; int eof; } ;
typedef  TYPE_1__ stream_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ KEEP_PLAYING ; 
 int /*<<< orphan*/  MP_ERR (struct MPContext*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_MSG (struct MPContext*,int /*<<< orphan*/ ,char*,long long,long long) ; 
 int /*<<< orphan*/  MSGL_STATUS ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_stream (TYPE_1__*) ; 
 int fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_idle (struct MPContext*) ; 
 int /*<<< orphan*/  mp_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 scalar_t__ stream_get_size (TYPE_1__*) ; 
 TYPE_1__* stream_open (char const*,int /*<<< orphan*/ ) ; 
 int stream_read (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

int stream_dump(struct MPContext *mpctx, const char *source_filename)
{
    struct MPOpts *opts = mpctx->opts;
    stream_t *stream = stream_open(source_filename, mpctx->global);
    if (!stream)
        return -1;

    int64_t size = stream_get_size(stream);

    FILE *dest = fopen(opts->stream_dump, "wb");
    if (!dest) {
        MP_ERR(mpctx, "Error opening dump file: %s\n", mp_strerror(errno));
        return -1;
    }

    bool ok = true;

    while (mpctx->stop_play == KEEP_PLAYING && ok) {
        if (!opts->quiet && ((stream->pos / (1024 * 1024)) % 2) == 1) {
            uint64_t pos = stream->pos;
            MP_MSG(mpctx, MSGL_STATUS, "Dumping %lld/%lld...",
                   (long long int)pos, (long long int)size);
        }
        uint8_t buf[4096];
        int len = stream_read(stream, buf, sizeof(buf));
        if (!len) {
            ok &= stream->eof;
            break;
        }
        ok &= fwrite(buf, len, 1, dest) == 1;
        mp_wakeup_core(mpctx); // don't actually sleep
        mp_idle(mpctx); // but process input
    }

    ok &= fclose(dest) == 0;
    free_stream(stream);
    return ok ? 0 : -1;
}