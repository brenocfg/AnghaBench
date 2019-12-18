#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8_t ;
typedef  size_t u32_t ;
struct TYPE_5__ {scalar_t__ score; size_t name_hash; } ;
typedef  TYPE_1__ spiffs_fd ;
struct TYPE_6__ {size_t fd_count; scalar_t__ fd_space; } ;
typedef  TYPE_2__ spiffs ;

/* Variables and functions */
 size_t spiffs_hash (TYPE_2__*,int /*<<< orphan*/  const*) ; 

void spiffs_fd_temporal_cache_rehash(
    spiffs *fs,
    const char *old_path,
    const char *new_path) {
  u32_t i;
  u32_t old_hash = spiffs_hash(fs, (const u8_t *)old_path);
  u32_t new_hash = spiffs_hash(fs, (const u8_t *)new_path);
  spiffs_fd *fds = (spiffs_fd *)fs->fd_space;
  for (i = 0; i < fs->fd_count; i++) {
    spiffs_fd *cur_fd = &fds[i];
    if (cur_fd->score > 0 && cur_fd->name_hash == old_hash) {
      cur_fd->name_hash = new_hash;
    }
  }
}