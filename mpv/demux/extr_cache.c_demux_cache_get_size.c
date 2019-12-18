#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct demux_cache {int /*<<< orphan*/  file_size; } ;

/* Variables and functions */

uint64_t demux_cache_get_size(struct demux_cache *cache)
{
    return cache->file_size;
}