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
typedef  size_t u32_t ;
struct TYPE_5__ {size_t file_nbr; } ;
typedef  TYPE_1__ spiffs_fd ;
struct TYPE_6__ {size_t fd_count; scalar_t__ fd_space; } ;
typedef  TYPE_2__ spiffs ;
typedef  int /*<<< orphan*/  s32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_ERR_OUT_OF_FILE_DESCS ; 
 int /*<<< orphan*/  SPIFFS_OK ; 

s32_t spiffs_fd_find_new(spiffs *fs, spiffs_fd **fd, const char *name) {
#if SPIFFS_TEMPORAL_FD_CACHE
  u32_t i;
  u16_t min_score = 0xffff;
  u32_t cand_ix = (u32_t)-1;
  u32_t name_hash = name ? spiffs_hash(fs, (const u8_t *)name) : 0;
  spiffs_fd *fds = (spiffs_fd *)fs->fd_space;

  if (name) {
    // first, decrease score of all closed descriptors
    for (i = 0; i < fs->fd_count; i++) {
      spiffs_fd *cur_fd = &fds[i];
      if (cur_fd->file_nbr == 0) {
        if (cur_fd->score > 1) { // score == 0 indicates never used fd
          cur_fd->score--;
        }
      }
    }
  }

  // find the free fd with least score or name match
  for (i = 0; i < fs->fd_count; i++) {
    spiffs_fd *cur_fd = &fds[i];
    if (cur_fd->file_nbr == 0) {
      if (name && cur_fd->name_hash == name_hash) {
        cand_ix = i;
        break;
      }
      if (cur_fd->score < min_score) {
        min_score = cur_fd->score;
        cand_ix = i;
      }
    }
  }

  if (cand_ix != (u32_t)-1) {
    spiffs_fd *cur_fd = &fds[cand_ix];
    if (name) {
      if (cur_fd->name_hash == name_hash && cur_fd->score > 0) {
        // opened an fd with same name hash, assume same file
        // set search point to saved obj index page and hope we have a correct match directly
        // when start searching - if not, we will just keep searching until it is found
        fs->cursor_block_ix = SPIFFS_BLOCK_FOR_PAGE(fs, cur_fd->objix_hdr_pix);
        fs->cursor_obj_lu_entry = SPIFFS_OBJ_LOOKUP_ENTRY_FOR_PAGE(fs, cur_fd->objix_hdr_pix);
        // update score
        if (cur_fd->score < 0xffff-SPIFFS_TEMPORAL_CACHE_HIT_SCORE) {
          cur_fd->score += SPIFFS_TEMPORAL_CACHE_HIT_SCORE;
        } else {
          cur_fd->score = 0xffff;
        }
      } else {
        // no hash hit, restore this fd to initial state
        cur_fd->score = SPIFFS_TEMPORAL_CACHE_HIT_SCORE;
        cur_fd->name_hash = name_hash;
      }
    }
    cur_fd->file_nbr = cand_ix+1;
    *fd = cur_fd;
    return SPIFFS_OK;
  } else {
    return SPIFFS_ERR_OUT_OF_FILE_DESCS;
  }
#else
  (void)name;
  u32_t i;
  spiffs_fd *fds = (spiffs_fd *)fs->fd_space;
  for (i = 0; i < fs->fd_count; i++) {
    spiffs_fd *cur_fd = &fds[i];
    if (cur_fd->file_nbr == 0) {
      cur_fd->file_nbr = i+1;
      *fd = cur_fd;
      return SPIFFS_OK;
    }
  }
  return SPIFFS_ERR_OUT_OF_FILE_DESCS;
#endif
}