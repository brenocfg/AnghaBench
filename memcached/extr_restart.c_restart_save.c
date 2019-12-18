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
struct TYPE_5__ {char* tag; scalar_t__ (* scb ) (char*,TYPE_2__*,int /*<<< orphan*/ ) ;struct TYPE_5__* next; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ restart_data_cb ;
struct TYPE_6__ {int /*<<< orphan*/ * f; } ;
typedef  TYPE_2__ restart_cb_ctx ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int S_IRUSR ; 
 int S_IWUSR ; 
 char* calloc (int,size_t) ; 
 TYPE_1__* cb_stack ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  perror (char*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ stub1 (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int umask (int) ; 

__attribute__((used)) static int restart_save(const char *file) {
    // metadata is kept in a separate file.
    // FIXME: function.
    size_t flen = strlen(file);
    const char *ext = ".meta";
    char *metafile = calloc(1, flen + strlen(ext) + 1);
    memcpy(metafile, file, flen);
    memcpy(metafile+flen, ext, strlen(ext));

    // restrictive permissions for the metadata file.
    // TODO: also for the mmap file eh? :P
    mode_t oldmask = umask(~(S_IRUSR | S_IWUSR));
    FILE *f = fopen(metafile, "w");
    umask(oldmask);
    if (f == NULL) {
        // FIXME: correct error handling.
        perror("failed to write metadata file");
        return -1;
    }

    restart_data_cb *cb = cb_stack;
    restart_cb_ctx ctx;
    ctx.f = f;
    while (cb != NULL) {
        // Plugins/engines in the metadata file are separated by tag lines.
        fprintf(f, "T%s\n", cb->tag);
        if (cb->scb(cb->tag, &ctx, cb->data) != 0) {
            return -1;
        }

        cb = cb->next;
    }

    fclose(f);
    free(metafile);

    return 0;
}