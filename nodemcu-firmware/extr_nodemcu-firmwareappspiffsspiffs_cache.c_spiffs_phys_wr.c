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
typedef  int /*<<< orphan*/  u32_t ;
typedef  int /*<<< orphan*/  spiffs_page_ix ;
typedef  int /*<<< orphan*/  spiffs_file ;
struct TYPE_6__ {int flags; scalar_t__ last_access; int /*<<< orphan*/  ix; } ;
typedef  TYPE_1__ spiffs_cache_page ;
struct TYPE_7__ {scalar_t__ last_access; } ;
typedef  TYPE_2__ spiffs_cache ;
typedef  int /*<<< orphan*/  spiffs ;
typedef  int /*<<< orphan*/  s32_t ;

/* Variables and functions */
 int SPIFFS_CACHE_FLAG_WRTHRU ; 
 int /*<<< orphan*/  SPIFFS_HAL_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SPIFFS_OK ; 
 int SPIFFS_OP_COM_MASK ; 
 int SPIFFS_OP_C_DELE ; 
 int SPIFFS_OP_C_WRTHRU ; 
 int SPIFFS_OP_TYPE_MASK ; 
 int SPIFFS_OP_T_OBJ_LU ; 
 int /*<<< orphan*/  SPIFFS_PADDR_TO_PAGE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t SPIFFS_PADDR_TO_PAGE_OFFSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _SPIFFS_MEMCPY (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spiffs_cache_page_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* spiffs_cache_page_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* spiffs_get_cache (int /*<<< orphan*/ *) ; 
 int* spiffs_get_cache_page (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

s32_t spiffs_phys_wr(
    spiffs *fs,
    u8_t op,
    spiffs_file fh,
    u32_t addr,
    u32_t len,
    u8_t *src) {
  (void)fh;
  spiffs_page_ix pix = SPIFFS_PADDR_TO_PAGE(fs, addr);
  spiffs_cache *cache = spiffs_get_cache(fs);
  spiffs_cache_page *cp =  spiffs_cache_page_get(fs, pix);

  if (cp && (op & SPIFFS_OP_COM_MASK) != SPIFFS_OP_C_WRTHRU) {
    // have a cache page
    // copy in data to cache page

    if ((op & SPIFFS_OP_COM_MASK) == SPIFFS_OP_C_DELE &&
        (op & SPIFFS_OP_TYPE_MASK) != SPIFFS_OP_T_OBJ_LU) {
      // page is being deleted, wipe from cache - unless it is a lookup page
      spiffs_cache_page_free(fs, cp->ix, 0);
      return SPIFFS_HAL_WRITE(fs, addr, len, src);
    }

    u8_t *mem =  spiffs_get_cache_page(fs, cache, cp->ix);
    _SPIFFS_MEMCPY(&mem[SPIFFS_PADDR_TO_PAGE_OFFSET(fs, addr)], src, len);

    cache->last_access++;
    cp->last_access = cache->last_access;

    if (cp->flags & SPIFFS_CACHE_FLAG_WRTHRU) {
      // page is being updated, no write-cache, just pass thru
      return SPIFFS_HAL_WRITE(fs, addr, len, src);
    } else {
      return SPIFFS_OK;
    }
  } else {
    // no cache page, no write cache - just write thru
    return SPIFFS_HAL_WRITE(fs, addr, len, src);
  }
}