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
typedef  int u8_t ;
typedef  int u32_t ;
typedef  int /*<<< orphan*/  spiffs ;

/* Variables and functions */
 int SPIFFS_OBJ_NAME_LEN ; 

__attribute__((used)) static u32_t spiffs_hash(spiffs *fs, const u8_t *name) {
  (void)fs;
  u32_t hash = 5381;
  u8_t c;
  int i = 0;
  while ((c = name[i++]) && i < SPIFFS_OBJ_NAME_LEN) {
    hash = (hash * 33) ^ c;
  }
  return hash;
}