#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ flushing_errors; scalar_t__ fs_errors; scalar_t__ io_errors; scalar_t__ journalfile_deletions; scalar_t__ journalfile_creations; scalar_t__ datafile_deletions; scalar_t__ datafile_creations; scalar_t__ io_read_extents; scalar_t__ io_read_extent_bytes; scalar_t__ io_write_extents; scalar_t__ io_write_extent_bytes; scalar_t__ io_read_requests; scalar_t__ io_read_bytes; scalar_t__ io_write_requests; scalar_t__ io_write_bytes; scalar_t__ after_decompress_bytes; scalar_t__ before_decompress_bytes; scalar_t__ after_compress_bytes; scalar_t__ before_compress_bytes; scalar_t__ pg_cache_evictions; scalar_t__ pg_cache_backfills; scalar_t__ pg_cache_misses; scalar_t__ pg_cache_hits; scalar_t__ pg_cache_deletions; scalar_t__ pg_cache_insertions; scalar_t__ page_cache_descriptors; scalar_t__ metric_API_consumers; scalar_t__ metric_API_producers; } ;
struct TYPE_3__ {scalar_t__ nr_committed_pages; } ;
struct page_cache {TYPE_1__ committed_page_index; scalar_t__ populated_pages; scalar_t__ page_descriptors; } ;
struct rrdengine_instance {TYPE_2__ stats; struct page_cache pg_cache; } ;

/* Variables and functions */
 scalar_t__ global_flushing_errors ; 
 scalar_t__ global_fs_errors ; 
 scalar_t__ global_io_errors ; 
 scalar_t__ rrdeng_reserved_file_descriptors ; 
 int /*<<< orphan*/  snprintfz (char*,size_t,char*,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long,long) ; 

char *get_rrdeng_statistics(struct rrdengine_instance *ctx, char *str, size_t size)
{
    struct page_cache *pg_cache;

    pg_cache = &ctx->pg_cache;
    snprintfz(str, size,
              "metric_API_producers: %ld\n"
              "metric_API_consumers: %ld\n"
              "page_cache_total_pages: %ld\n"
              "page_cache_descriptors: %ld\n"
              "page_cache_populated_pages: %ld\n"
              "page_cache_committed_pages: %ld\n"
              "page_cache_insertions: %ld\n"
              "page_cache_deletions: %ld\n"
              "page_cache_hits: %ld\n"
              "page_cache_misses: %ld\n"
              "page_cache_backfills: %ld\n"
              "page_cache_evictions: %ld\n"
              "compress_before_bytes: %ld\n"
              "compress_after_bytes: %ld\n"
              "decompress_before_bytes: %ld\n"
              "decompress_after_bytes: %ld\n"
              "io_write_bytes: %ld\n"
              "io_write_requests: %ld\n"
              "io_read_bytes: %ld\n"
              "io_read_requests: %ld\n"
              "io_write_extent_bytes: %ld\n"
              "io_write_extents: %ld\n"
              "io_read_extent_bytes: %ld\n"
              "io_read_extents: %ld\n"
              "datafile_creations: %ld\n"
              "datafile_deletions: %ld\n"
              "journalfile_creations: %ld\n"
              "journalfile_deletions: %ld\n"
              "io_errors: %ld\n"
              "fs_errors: %ld\n"
              "global_io_errors: %ld\n"
              "global_fs_errors: %ld\n"
              "rrdeng_reserved_file_descriptors: %ld\n"
              "flushing_errors: %ld\n"
              "global_flushing_errors: %ld\n",
              (long)ctx->stats.metric_API_producers,
              (long)ctx->stats.metric_API_consumers,
              (long)pg_cache->page_descriptors,
              (long)ctx->stats.page_cache_descriptors,
              (long)pg_cache->populated_pages,
              (long)pg_cache->committed_page_index.nr_committed_pages,
              (long)ctx->stats.pg_cache_insertions,
              (long)ctx->stats.pg_cache_deletions,
              (long)ctx->stats.pg_cache_hits,
              (long)ctx->stats.pg_cache_misses,
              (long)ctx->stats.pg_cache_backfills,
              (long)ctx->stats.pg_cache_evictions,
              (long)ctx->stats.before_compress_bytes,
              (long)ctx->stats.after_compress_bytes,
              (long)ctx->stats.before_decompress_bytes,
              (long)ctx->stats.after_decompress_bytes,
              (long)ctx->stats.io_write_bytes,
              (long)ctx->stats.io_write_requests,
              (long)ctx->stats.io_read_bytes,
              (long)ctx->stats.io_read_requests,
              (long)ctx->stats.io_write_extent_bytes,
              (long)ctx->stats.io_write_extents,
              (long)ctx->stats.io_read_extent_bytes,
              (long)ctx->stats.io_read_extents,
              (long)ctx->stats.datafile_creations,
              (long)ctx->stats.datafile_deletions,
              (long)ctx->stats.journalfile_creations,
              (long)ctx->stats.journalfile_deletions,
              (long)ctx->stats.io_errors,
              (long)ctx->stats.fs_errors,
              (long)global_io_errors,
              (long)global_fs_errors,
              (long)rrdeng_reserved_file_descriptors,
              (long)ctx->stats.flushing_errors,
              (long)global_flushing_errors
    );
    return str;
}