#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ spiffs_block_ix ;
struct TYPE_9__ {scalar_t__ block_count; scalar_t__ max_erase_count; int /*<<< orphan*/  err_code; } ;
typedef  TYPE_1__ spiffs ;
typedef  int s32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_API_CHECK_CFG (TYPE_1__*) ; 
 int /*<<< orphan*/  SPIFFS_API_CHECK_RES_UNLOCK (TYPE_1__*,int) ; 
 scalar_t__ SPIFFS_CHECK_MOUNT (TYPE_1__*) ; 
 int SPIFFS_ERR_ERASE_FAIL ; 
 int /*<<< orphan*/  SPIFFS_ERR_MOUNTED ; 
 int SPIFFS_ERR_RO_NOT_IMPL ; 
 int /*<<< orphan*/  SPIFFS_LOCK (TYPE_1__*) ; 
 int SPIFFS_OK ; 
 int /*<<< orphan*/  SPIFFS_UNLOCK (TYPE_1__*) ; 
 int spiffs_erase_block (TYPE_1__*,scalar_t__) ; 

s32_t SPIFFS_format(spiffs *fs) {
#if SPIFFS_READ_ONLY
  (void)fs;
  return SPIFFS_ERR_RO_NOT_IMPL;
#else
  SPIFFS_API_CHECK_CFG(fs);
  if (SPIFFS_CHECK_MOUNT(fs)) {
    fs->err_code = SPIFFS_ERR_MOUNTED;
    return -1;
  }

  s32_t res;
  SPIFFS_LOCK(fs);

  spiffs_block_ix bix = 0;
  while (bix < fs->block_count) {
    fs->max_erase_count = 0;
    res = spiffs_erase_block(fs, bix);
    if (res != SPIFFS_OK) {
      res = SPIFFS_ERR_ERASE_FAIL;
    }
    SPIFFS_API_CHECK_RES_UNLOCK(fs, res);
    bix++;
  }

  SPIFFS_UNLOCK(fs);

  return 0;
#endif // SPIFFS_READ_ONLY
}