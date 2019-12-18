#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {char* value; } ;
typedef  TYPE_2__ token_t ;
struct TYPE_22__ {char* buffer; unsigned int offset; } ;
struct TYPE_24__ {TYPE_1__ stats; } ;
typedef  TYPE_3__ conn ;
struct TYPE_25__ {int /*<<< orphan*/  dump_enabled; } ;

/* Variables and functions */
 unsigned int MAX_NUMBER_OF_SLAB_CLASSES ; 
 size_t SUBCOMMAND_TOKEN ; 
 int /*<<< orphan*/  append_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ get_stats (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*),TYPE_3__*) ; 
 char* item_cachedump (unsigned int,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  out_of_memory (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  out_string (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  process_extstore_stats (int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*),TYPE_3__*) ; 
 int /*<<< orphan*/  process_stat_settings (int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*),TYPE_3__*) ; 
 int /*<<< orphan*/  process_stats_conns (int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*),TYPE_3__*) ; 
 int /*<<< orphan*/  process_stats_detail (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  safe_strtoul (char*,unsigned int*) ; 
 int /*<<< orphan*/  server_stats (int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*),TYPE_3__*) ; 
 TYPE_5__ settings ; 
 int /*<<< orphan*/  stats_reset () ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  write_and_free (TYPE_3__*,char*,unsigned int) ; 

__attribute__((used)) static void process_stat(conn *c, token_t *tokens, const size_t ntokens) {
    const char *subcommand = tokens[SUBCOMMAND_TOKEN].value;
    assert(c != NULL);

    if (ntokens < 2) {
        out_string(c, "CLIENT_ERROR bad command line");
        return;
    }

    if (ntokens == 2) {
        server_stats(&append_stats, c);
        (void)get_stats(NULL, 0, &append_stats, c);
    } else if (strcmp(subcommand, "reset") == 0) {
        stats_reset();
        out_string(c, "RESET");
        return ;
    } else if (strcmp(subcommand, "detail") == 0) {
        /* NOTE: how to tackle detail with binary? */
        if (ntokens < 4)
            process_stats_detail(c, "");  /* outputs the error message */
        else
            process_stats_detail(c, tokens[2].value);
        /* Output already generated */
        return ;
    } else if (strcmp(subcommand, "settings") == 0) {
        process_stat_settings(&append_stats, c);
    } else if (strcmp(subcommand, "cachedump") == 0) {
        char *buf;
        unsigned int bytes, id, limit = 0;

        if (!settings.dump_enabled) {
            out_string(c, "CLIENT_ERROR stats cachedump not allowed");
            return;
        }

        if (ntokens < 5) {
            out_string(c, "CLIENT_ERROR bad command line");
            return;
        }

        if (!safe_strtoul(tokens[2].value, &id) ||
            !safe_strtoul(tokens[3].value, &limit)) {
            out_string(c, "CLIENT_ERROR bad command line format");
            return;
        }

        if (id >= MAX_NUMBER_OF_SLAB_CLASSES) {
            out_string(c, "CLIENT_ERROR Illegal slab id");
            return;
        }

        buf = item_cachedump(id, limit, &bytes);
        write_and_free(c, buf, bytes);
        return ;
    } else if (strcmp(subcommand, "conns") == 0) {
        process_stats_conns(&append_stats, c);
#ifdef EXTSTORE
    } else if (strcmp(subcommand, "extstore") == 0) {
        process_extstore_stats(&append_stats, c);
#endif
    } else {
        /* getting here means that the subcommand is either engine specific or
           is invalid. query the engine and see. */
        if (get_stats(subcommand, strlen(subcommand), &append_stats, c)) {
            if (c->stats.buffer == NULL) {
                out_of_memory(c, "SERVER_ERROR out of memory writing stats");
            } else {
                write_and_free(c, c->stats.buffer, c->stats.offset);
                c->stats.buffer = NULL;
            }
        } else {
            out_string(c, "ERROR");
        }
        return ;
    }

    /* append terminator and start the transfer */
    append_stats(NULL, 0, NULL, 0, c);

    if (c->stats.buffer == NULL) {
        out_of_memory(c, "SERVER_ERROR out of memory writing stats");
    } else {
        write_and_free(c, c->stats.buffer, c->stats.offset);
        c->stats.buffer = NULL;
    }
}