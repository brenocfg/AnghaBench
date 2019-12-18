#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ restart_data_cb ;
struct TYPE_5__ {char* line; int done; TYPE_1__* cb; int /*<<< orphan*/  f; } ;
typedef  TYPE_2__ restart_cb_ctx ;
typedef  enum restart_get_kv_ret { ____Placeholder_restart_get_kv_ret } restart_get_kv_ret ;

/* Variables and functions */
 int RESTART_BADLINE ; 
 int RESTART_DONE ; 
 int RESTART_NOTAG ; 
 int RESTART_OK ; 
 TYPE_1__* cb_stack ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

enum restart_get_kv_ret restart_get_kv(void *ctx, char **key, char **val) {
    char *line = NULL;
    size_t len = 0;
    restart_data_cb *cb = NULL;
    restart_cb_ctx *c = (restart_cb_ctx *) ctx;
    // free previous line.
    // we could just pass it into getline, but it can randomly realloc so we'd
    // have to re-assign it into the structure anyway.
    if (c->line != NULL) {
        free(c->line);
    }

    if (getline(&line, &len, c->f) != -1) {
        // First char is an indicator:
        // T for TAG, changing the callback we use.
        // K for key/value, to ship to the active callback.
        char *p = line;
        while (*p != '\n') {
            p++;
        }
        *p = '\0';

        if (line[0] == 'T') {
            cb = cb_stack;
            while (cb != NULL) {
                // NOTE: len is allocated size, not line len. need to chomp \n
                if (strcmp(cb->tag, line+1) == 0) {
                    break;
                }
                cb = cb->next;
            }
            if (cb == NULL) {
                fprintf(stderr, "[restart] internal handler for metadata tag not found: %s:\n", line+1);
                return RESTART_NOTAG;
            }
            c->cb = cb;
        } else if (line[0] == 'K') {
            char *p = line+1; // start just ahead of the token.
            // tokenize the string and return the pointers?
            if (key != NULL) {
                *key = p;
            }

            // turn key into a normal NULL terminated string.
            while (*p != ' ' && (p - line < len)) {
                p++;
            }
            *p = '\0';
            p++;

            // value _should_ run until where the newline was, which is \0 now
            if (val != NULL) {
                *val = p;
            }
            c->line = line;

            return RESTART_OK;
        } else {
            // FIXME: proper error chain.
            fprintf(stderr, "[restart] invalid metadata line:\n\n%s\n", line);
            return RESTART_BADLINE;
        }
    } else {
        // EOF or error in read.
        c->done = true;
    }

    return RESTART_DONE;
}