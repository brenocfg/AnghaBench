#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32_t ;
typedef  int spiffs_obj_id ;
struct TYPE_4__ {scalar_t__ work; } ;
typedef  TYPE_1__ spiffs ;

/* Variables and functions */
 int SPIFFS_CFG_LOG_PAGE_SZ (TYPE_1__*) ; 
 int SPIFFS_OBJ_ID_IX_FLAG ; 

__attribute__((used)) static int spiffs_object_index_search(spiffs *fs, spiffs_obj_id obj_id) {
  u32_t i;
  spiffs_obj_id *obj_table = (spiffs_obj_id *)fs->work;
  obj_id &= ~SPIFFS_OBJ_ID_IX_FLAG;
  for (i = 0; i < SPIFFS_CFG_LOG_PAGE_SZ(fs) / sizeof(spiffs_obj_id); i++) {
    if ((obj_table[i] & ~SPIFFS_OBJ_ID_IX_FLAG) == obj_id) {
      return i;
    }
  }
  return -1;
}