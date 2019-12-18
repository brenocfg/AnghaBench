#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int cpage_count; int cpage_use_map; int cpage_use_mask; struct TYPE_13__* cpages; } ;
typedef  TYPE_1__ u8_t ;
typedef  int u32_t ;
typedef  TYPE_1__ spiffs_cache ;
struct TYPE_14__ {scalar_t__ cache; int cache_size; } ;
typedef  TYPE_3__ spiffs ;
struct TYPE_15__ {int ix; } ;

/* Variables and functions */
 int SPIFFS_CACHE_PAGE_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  _SPIFFS_MEMCPY (scalar_t__,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* spiffs_get_cache (TYPE_3__*) ; 
 TYPE_4__* spiffs_get_cache_page_hdr (TYPE_3__*,TYPE_1__*,int) ; 

void spiffs_cache_init(spiffs *fs) {
  if (fs->cache == 0) return;
  u32_t sz = fs->cache_size;
  u32_t cache_mask = 0;
  int i;
  int cache_entries =
      (sz - sizeof(spiffs_cache)) / (SPIFFS_CACHE_PAGE_SIZE(fs));
  if (cache_entries <= 0) return;

  for (i = 0; i < cache_entries; i++) {
    cache_mask <<= 1;
    cache_mask |= 1;
  }

  spiffs_cache cache;
  memset(&cache, 0, sizeof(spiffs_cache));
  cache.cpage_count = cache_entries;
  cache.cpages = (u8_t *)((u8_t *)fs->cache + sizeof(spiffs_cache));

  cache.cpage_use_map = 0xffffffff;
  cache.cpage_use_mask = cache_mask;
  _SPIFFS_MEMCPY(fs->cache, &cache, sizeof(spiffs_cache));

  spiffs_cache *c = spiffs_get_cache(fs);

  memset(c->cpages, 0, c->cpage_count * SPIFFS_CACHE_PAGE_SIZE(fs));

  c->cpage_use_map &= ~(c->cpage_use_mask);
  for (i = 0; i < cache.cpage_count; i++) {
    spiffs_get_cache_page_hdr(fs, c, i)->ix = i;
  }
}