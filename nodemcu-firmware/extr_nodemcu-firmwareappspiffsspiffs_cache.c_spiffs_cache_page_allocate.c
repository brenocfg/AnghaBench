#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  last_access; } ;
typedef  TYPE_1__ spiffs_cache_page ;
struct TYPE_8__ {int cpage_use_map; int cpage_count; int /*<<< orphan*/  last_access; } ;
typedef  TYPE_2__ spiffs_cache ;
typedef  int /*<<< orphan*/  spiffs ;

/* Variables and functions */
 TYPE_2__* spiffs_get_cache (int /*<<< orphan*/ *) ; 
 TYPE_1__* spiffs_get_cache_page_hdr (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

__attribute__((used)) static spiffs_cache_page *spiffs_cache_page_allocate(spiffs *fs) {
  spiffs_cache *cache = spiffs_get_cache(fs);
  if (cache->cpage_use_map == 0xffffffff) {
    // out of cache memory
    return 0;
  }
  int i;
  for (i = 0; i < cache->cpage_count; i++) {
    if ((cache->cpage_use_map & (1<<i)) == 0) {
      spiffs_cache_page *cp = spiffs_get_cache_page_hdr(fs, cache, i);
      cache->cpage_use_map |= (1<<i);
      cp->last_access = cache->last_access;
      //SPIFFS_CACHE_DBG("CACHE_ALLO: allocated cache page "_SPIPRIi"\n", i);
      return cp;
    }
  }
  // out of cache entries
  return 0;
}