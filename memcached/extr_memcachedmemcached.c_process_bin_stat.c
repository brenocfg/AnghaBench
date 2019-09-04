#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/ * buffer; int /*<<< orphan*/  offset; } ;
struct TYPE_18__ {size_t keylen; } ;
struct TYPE_19__ {TYPE_1__ request; } ;
struct TYPE_21__ {int sfd; TYPE_3__ stats; TYPE_2__ binary_header; } ;
typedef  TYPE_4__ conn ;
struct TYPE_22__ {int verbose; int detail_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_KEY_ENOENT ; 
 int /*<<< orphan*/  append_stats (char*,int /*<<< orphan*/ ,char*,int,TYPE_4__*) ; 
 char* binary_get_key (TYPE_4__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_stats (char*,size_t,int /*<<< orphan*/  (*) (char*,int /*<<< orphan*/ ,char*,int,TYPE_4__*),TYPE_4__*) ; 
 int /*<<< orphan*/  out_of_memory (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  process_stat_settings (int /*<<< orphan*/  (*) (char*,int /*<<< orphan*/ ,char*,int,TYPE_4__*),TYPE_4__*) ; 
 int /*<<< orphan*/  server_stats (int /*<<< orphan*/  (*) (char*,int /*<<< orphan*/ ,char*,int,TYPE_4__*),TYPE_4__*) ; 
 TYPE_7__ settings ; 
 char* stats_prefix_dump (int*) ; 
 int /*<<< orphan*/  stats_reset () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  write_and_free (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_bin_error (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_bin_stat(conn *c) {
    char *subcommand = binary_get_key(c);
    size_t nkey = c->binary_header.request.keylen;

    if (settings.verbose > 1) {
        int ii;
        fprintf(stderr, "<%d STATS ", c->sfd);
        for (ii = 0; ii < nkey; ++ii) {
            fprintf(stderr, "%c", subcommand[ii]);
        }
        fprintf(stderr, "\n");
    }

    if (nkey == 0) {
        /* request all statistics */
        server_stats(&append_stats, c);
        (void)get_stats(NULL, 0, &append_stats, c);
    } else if (strncmp(subcommand, "reset", 5) == 0) {
        stats_reset();
    } else if (strncmp(subcommand, "settings", 8) == 0) {
        process_stat_settings(&append_stats, c);
    } else if (strncmp(subcommand, "detail", 6) == 0) {
        char *subcmd_pos = subcommand + 6;
        if (strncmp(subcmd_pos, " dump", 5) == 0) {
            int len;
            char *dump_buf = stats_prefix_dump(&len);
            if (dump_buf == NULL || len <= 0) {
                out_of_memory(c, "SERVER_ERROR Out of memory generating stats");
                if (dump_buf != NULL)
                    free(dump_buf);
                return;
            } else {
                append_stats("detailed", strlen("detailed"), dump_buf, len, c);
                free(dump_buf);
            }
        } else if (strncmp(subcmd_pos, " on", 3) == 0) {
            settings.detail_enabled = 1;
        } else if (strncmp(subcmd_pos, " off", 4) == 0) {
            settings.detail_enabled = 0;
        } else {
            write_bin_error(c, PROTOCOL_BINARY_RESPONSE_KEY_ENOENT, NULL, 0);
            return;
        }
    } else {
        if (get_stats(subcommand, nkey, &append_stats, c)) {
            if (c->stats.buffer == NULL) {
                out_of_memory(c, "SERVER_ERROR Out of memory generating stats");
            } else {
                write_and_free(c, c->stats.buffer, c->stats.offset);
                c->stats.buffer = NULL;
            }
        } else {
            write_bin_error(c, PROTOCOL_BINARY_RESPONSE_KEY_ENOENT, NULL, 0);
        }

        return;
    }

    /* Append termination package and start the transfer */
    append_stats(NULL, 0, NULL, 0, c);
    if (c->stats.buffer == NULL) {
        out_of_memory(c, "SERVER_ERROR Out of memory preparing to send stats");
    } else {
        write_and_free(c, c->stats.buffer, c->stats.offset);
        c->stats.buffer = NULL;
    }
}