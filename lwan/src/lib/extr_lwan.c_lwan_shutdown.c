#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  config_file_path; int /*<<< orphan*/  error_template; int /*<<< orphan*/  listener; } ;
struct lwan {int /*<<< orphan*/  conns; int /*<<< orphan*/  url_map_trie; TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_fd_watch_shutdown (struct lwan*) ; 
 int /*<<< orphan*/  lwan_http_authorize_shutdown () ; 
 int /*<<< orphan*/  lwan_job_thread_shutdown () ; 
 int /*<<< orphan*/  lwan_readahead_shutdown () ; 
 int /*<<< orphan*/  lwan_response_shutdown (struct lwan*) ; 
 int /*<<< orphan*/  lwan_status_debug (char*) ; 
 int /*<<< orphan*/  lwan_status_info (char*) ; 
 int /*<<< orphan*/  lwan_status_shutdown (struct lwan*) ; 
 int /*<<< orphan*/  lwan_tables_shutdown () ; 
 int /*<<< orphan*/  lwan_thread_shutdown (struct lwan*) ; 
 int /*<<< orphan*/  lwan_trie_destroy (int /*<<< orphan*/ *) ; 

void lwan_shutdown(struct lwan *l)
{
    lwan_status_info("Shutting down");

    free(l->config.listener);
    free(l->config.error_template);
    free(l->config.config_file_path);

    lwan_job_thread_shutdown();
    lwan_thread_shutdown(l);

    lwan_status_debug("Shutting down URL handlers");
    lwan_trie_destroy(&l->url_map_trie);

    free(l->conns);

    lwan_response_shutdown(l);
    lwan_tables_shutdown();
    lwan_status_shutdown(l);
    lwan_http_authorize_shutdown();
    lwan_readahead_shutdown();
    lwan_fd_watch_shutdown(l);
}