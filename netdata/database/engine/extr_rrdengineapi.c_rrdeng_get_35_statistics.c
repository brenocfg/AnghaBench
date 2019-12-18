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
typedef  unsigned long long uint64_t ;
struct TYPE_4__ {scalar_t__ flushing_errors; scalar_t__ fs_errors; scalar_t__ io_errors; scalar_t__ page_cache_descriptors; scalar_t__ journalfile_deletions; scalar_t__ journalfile_creations; scalar_t__ datafile_deletions; scalar_t__ datafile_creations; scalar_t__ io_read_extents; scalar_t__ io_read_extent_bytes; scalar_t__ io_write_extents; scalar_t__ io_write_extent_bytes; scalar_t__ io_read_requests; scalar_t__ io_read_bytes; scalar_t__ io_write_requests; scalar_t__ io_write_bytes; scalar_t__ after_decompress_bytes; scalar_t__ before_decompress_bytes; scalar_t__ after_compress_bytes; scalar_t__ before_compress_bytes; scalar_t__ pg_cache_evictions; scalar_t__ pg_cache_backfills; scalar_t__ pg_cache_misses; scalar_t__ pg_cache_hits; scalar_t__ pg_cache_deletions; scalar_t__ pg_cache_insertions; scalar_t__ metric_API_consumers; scalar_t__ metric_API_producers; } ;
struct TYPE_3__ {scalar_t__ nr_committed_pages; } ;
struct page_cache {TYPE_1__ committed_page_index; scalar_t__ populated_pages; scalar_t__ page_descriptors; } ;
struct rrdengine_instance {TYPE_2__ stats; struct page_cache pg_cache; } ;

/* Variables and functions */
 int RRDENG_NR_STATS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ global_flushing_errors ; 
 scalar_t__ global_fs_errors ; 
 scalar_t__ global_io_errors ; 
 scalar_t__ rrdeng_reserved_file_descriptors ; 

void rrdeng_get_35_statistics(struct rrdengine_instance *ctx, unsigned long long *array)
{
    struct page_cache *pg_cache = &ctx->pg_cache;

    array[0] = (uint64_t)ctx->stats.metric_API_producers;
    array[1] = (uint64_t)ctx->stats.metric_API_consumers;
    array[2] = (uint64_t)pg_cache->page_descriptors;
    array[3] = (uint64_t)pg_cache->populated_pages;
    array[4] = (uint64_t)pg_cache->committed_page_index.nr_committed_pages;
    array[5] = (uint64_t)ctx->stats.pg_cache_insertions;
    array[6] = (uint64_t)ctx->stats.pg_cache_deletions;
    array[7] = (uint64_t)ctx->stats.pg_cache_hits;
    array[8] = (uint64_t)ctx->stats.pg_cache_misses;
    array[9] = (uint64_t)ctx->stats.pg_cache_backfills;
    array[10] = (uint64_t)ctx->stats.pg_cache_evictions;
    array[11] = (uint64_t)ctx->stats.before_compress_bytes;
    array[12] = (uint64_t)ctx->stats.after_compress_bytes;
    array[13] = (uint64_t)ctx->stats.before_decompress_bytes;
    array[14] = (uint64_t)ctx->stats.after_decompress_bytes;
    array[15] = (uint64_t)ctx->stats.io_write_bytes;
    array[16] = (uint64_t)ctx->stats.io_write_requests;
    array[17] = (uint64_t)ctx->stats.io_read_bytes;
    array[18] = (uint64_t)ctx->stats.io_read_requests;
    array[19] = (uint64_t)ctx->stats.io_write_extent_bytes;
    array[20] = (uint64_t)ctx->stats.io_write_extents;
    array[21] = (uint64_t)ctx->stats.io_read_extent_bytes;
    array[22] = (uint64_t)ctx->stats.io_read_extents;
    array[23] = (uint64_t)ctx->stats.datafile_creations;
    array[24] = (uint64_t)ctx->stats.datafile_deletions;
    array[25] = (uint64_t)ctx->stats.journalfile_creations;
    array[26] = (uint64_t)ctx->stats.journalfile_deletions;
    array[27] = (uint64_t)ctx->stats.page_cache_descriptors;
    array[28] = (uint64_t)ctx->stats.io_errors;
    array[29] = (uint64_t)ctx->stats.fs_errors;
    array[30] = (uint64_t)global_io_errors;
    array[31] = (uint64_t)global_fs_errors;
    array[32] = (uint64_t)rrdeng_reserved_file_descriptors;
    array[33] = (uint64_t)ctx->stats.flushing_errors;
    array[34] = (uint64_t)global_flushing_errors;
    assert(RRDENG_NR_STATS == 35);
}