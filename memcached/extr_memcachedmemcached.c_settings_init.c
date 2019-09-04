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
struct TYPE_2__ {int use_cas; int access; int port; int maxbytes; int maxconns; int evict_to_free; double factor; int chunk_size; int num_threads; char prefix_delimiter; int reqs_per_event; int backlog; int item_size_max; int slab_page_size; int slab_chunk_size_max; int sasl; int maxconns_fast; int lru_crawler; int lru_crawler_sleep; int lru_maintainer_thread; int lru_segmented; int hot_lru_pct; int warm_lru_pct; double hot_max_factor; double warm_max_factor; int inline_ascii_response; int temp_lru; int temporary_ttl; int slab_reassign; int slab_automove; double slab_automove_ratio; int slab_automove_window; int shutdown_command; int flush_enabled; int dump_enabled; int crawls_persleep; int drop_privileges; int /*<<< orphan*/  logger_buf_size; int /*<<< orphan*/  logger_watcher_buf_size; int /*<<< orphan*/  tail_repair_time; scalar_t__ hashpower_init; scalar_t__ idle_timeout; scalar_t__ lru_crawler_tocrawl; int /*<<< orphan*/  binding_protocol; scalar_t__ detail_enabled; scalar_t__ num_threads_per_udp; int /*<<< orphan*/ * socketpath; scalar_t__ oldest_cas; scalar_t__ oldest_live; scalar_t__ verbose; int /*<<< orphan*/ * inter; scalar_t__ udpport; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_BUF_SIZE ; 
 int /*<<< orphan*/  LOGGER_WATCHER_BUF_SIZE ; 
 int /*<<< orphan*/  TAIL_REPAIR_TIME_DEFAULT ; 
 int /*<<< orphan*/  negotiating_prot ; 
 TYPE_1__ settings ; 

__attribute__((used)) static void settings_init(void) {
    settings.use_cas = true;
    settings.access = 0700;
    settings.port = 11211;
    settings.udpport = 0;
#ifdef TLS
    settings.ssl_enabled = false;
    settings.ssl_ctx = NULL;
    settings.ssl_chain_cert = NULL;
    settings.ssl_key = NULL;
    settings.ssl_verify_mode = SSL_VERIFY_NONE;
    settings.ssl_keyformat = SSL_FILETYPE_PEM;
    settings.ssl_ciphers = NULL;
    settings.ssl_ca_cert = NULL;
    settings.ssl_last_cert_refresh_time = current_time;
    settings.ssl_wbuf_size = 16 * 1024; // default is 16KB (SSL max frame size is 17KB)
#endif
    /* By default this string should be NULL for getaddrinfo() */
    settings.inter = NULL;
    settings.maxbytes = 64 * 1024 * 1024; /* default is 64MB */
    settings.maxconns = 1024;         /* to limit connections-related memory to about 5MB */
    settings.verbose = 0;
    settings.oldest_live = 0;
    settings.oldest_cas = 0;          /* supplements accuracy of oldest_live */
    settings.evict_to_free = 1;       /* push old items out of cache when memory runs out */
    settings.socketpath = NULL;       /* by default, not using a unix socket */
    settings.factor = 1.25;
    settings.chunk_size = 48;         /* space for a modest key and value */
    settings.num_threads = 4;         /* N workers */
    settings.num_threads_per_udp = 0;
    settings.prefix_delimiter = ':';
    settings.detail_enabled = 0;
    settings.reqs_per_event = 20;
    settings.backlog = 1024;
    settings.binding_protocol = negotiating_prot;
    settings.item_size_max = 1024 * 1024; /* The famous 1MB upper limit. */
    settings.slab_page_size = 1024 * 1024; /* chunks are split from 1MB pages. */
    settings.slab_chunk_size_max = settings.slab_page_size / 2;
    settings.sasl = false;
    settings.maxconns_fast = true;
    settings.lru_crawler = false;
    settings.lru_crawler_sleep = 100;
    settings.lru_crawler_tocrawl = 0;
    settings.lru_maintainer_thread = false;
    settings.lru_segmented = true;
    settings.hot_lru_pct = 20;
    settings.warm_lru_pct = 40;
    settings.hot_max_factor = 0.2;
    settings.warm_max_factor = 2.0;
    settings.inline_ascii_response = false;
    settings.temp_lru = false;
    settings.temporary_ttl = 61;
    settings.idle_timeout = 0; /* disabled */
    settings.hashpower_init = 0;
    settings.slab_reassign = true;
    settings.slab_automove = 1;
    settings.slab_automove_ratio = 0.8;
    settings.slab_automove_window = 30;
    settings.shutdown_command = false;
    settings.tail_repair_time = TAIL_REPAIR_TIME_DEFAULT;
    settings.flush_enabled = true;
    settings.dump_enabled = true;
    settings.crawls_persleep = 1000;
    settings.logger_watcher_buf_size = LOGGER_WATCHER_BUF_SIZE;
    settings.logger_buf_size = LOGGER_BUF_SIZE;
    settings.drop_privileges = false;
#ifdef MEMCACHED_DEBUG
    settings.relaxed_privileges = false;
#endif
}