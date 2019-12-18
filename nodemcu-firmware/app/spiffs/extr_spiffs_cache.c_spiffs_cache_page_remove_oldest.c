#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8_t ;
typedef  scalar_t__ u32_t ;
struct TYPE_6__ {scalar_t__ last_access; int flags; } ;
typedef  TYPE_1__ spiffs_cache_page ;
struct TYPE_7__ {int cpage_use_map; int cpage_use_mask; int cpage_count; scalar_t__ last_access; } ;
typedef  TYPE_2__ spiffs_cache ;
typedef  int /*<<< orphan*/  spiffs ;
typedef  int /*<<< orphan*/  s32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_OK ; 
 int /*<<< orphan*/  spiffs_cache_page_free (int /*<<< orphan*/ *,int,int) ; 
 TYPE_2__* spiffs_get_cache (int /*<<< orphan*/ *) ; 
 TYPE_1__* spiffs_get_cache_page_hdr (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

__attribute__((used)) static s32_t spiffs_cache_page_remove_oldest(spiffs *fs, u8_t flag_mask, u8_t flags) {
  s32_t res = SPIFFS_OK;
  spiffs_cache *cache = spiffs_get_cache(fs);

  if ((cache->cpage_use_map & cache->cpage_use_mask) != cache->cpage_use_mask) {
    // at least one free cpage
    return SPIFFS_OK;
  }

  // all busy, scan thru all to find the cpage which has oldest access
  int i;
  int cand_ix = -1;
  u32_t oldest_val = 0;
  for (i = 0; i < cache->cpage_count; i++) {
    spiffs_cache_page *cp = spiffs_get_cache_page_hdr(fs, cache, i);
    if ((cache->last_access - cp->last_access) > oldest_val &&
        (cp->flags & flag_mask) == flags) {
      oldest_val = cache->last_access - cp->last_access;
      cand_ix = i;
    }
  }

  if (cand_ix >= 0) {
    res = spiffs_cache_page_free(fs, cand_ix, 1);
  }

  return res;
}