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
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ u32_t ;
typedef  int /*<<< orphan*/  s32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_OK ; 
 scalar_t__ flash ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static s32_t flash_write (u32_t addr, u32_t size, u8_t *src) {
  memcpy (flash + addr, src, size);
  return SPIFFS_OK;
}