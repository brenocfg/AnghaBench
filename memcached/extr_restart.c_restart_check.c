#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ (* ccb ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ restart_data_cb ;
struct TYPE_6__ {char* line; int done; TYPE_1__* cb; int /*<<< orphan*/ * f; } ;
typedef  TYPE_2__ restart_cb_ctx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ RESTART_DONE ; 
 int /*<<< orphan*/  abort () ; 
 char* calloc (int,size_t) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 scalar_t__ restart_get_kv (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char const*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int restart_check(const char *file) {
    // metadata is kept in a separate file.
    size_t flen = strlen(file);
    const char *ext = ".meta";
    char *metafile = calloc(1, flen + strlen(ext) + 1);
    memcpy(metafile, file, flen);
    memcpy(metafile+flen, ext, strlen(ext));

    FILE *f = fopen(metafile, "r");
    if (f == NULL) {
        fprintf(stderr, "[restart] no metadata save file, starting with a clean cache\n");
        return -1;
    }

    restart_cb_ctx ctx;

    ctx.f = f;
    ctx.cb = NULL;
    ctx.line = NULL;
    ctx.done = false;
    if (restart_get_kv(&ctx, NULL, NULL) != RESTART_DONE) {
        // First line must be a tag, so read it in and set up the proper
        // callback here.
        fprintf(stderr, "[restart] corrupt metadata file\n");
        // TODO: this should probably just return -1 and skip the reuse.
        abort();
    }
    if (ctx.cb == NULL) {
        fprintf(stderr, "[restart] Failed to read a tag from metadata file\n");
        abort();
    }

    // loop call the callback, check result code.
    bool failed = false;
    while (!ctx.done) {
        restart_data_cb *cb = ctx.cb;
        if (cb->ccb(cb->tag, &ctx, cb->data) != 0) {
            failed = true;
            break;
        }
    }

    if (ctx.line)
        free(ctx.line);

    fclose(f);

    unlink(metafile);
    free(metafile);

    if (failed) {
        fprintf(stderr, "[restart] failed to valiate metadata, starting with a clean cache\n");
        return -1;
    } else {
        return 0;
    }
}