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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  spiffs_file ;
struct TYPE_4__ {int flags; scalar_t__ size; scalar_t__ fdoffset; } ;
typedef  TYPE_1__ spiffs_fd ;
typedef  int /*<<< orphan*/  spiffs ;
typedef  scalar_t__ s32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_API_CHECK_CFG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPIFFS_API_CHECK_MOUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPIFFS_API_CHECK_RES_UNLOCK (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ SPIFFS_ERR_END_OF_OBJECT ; 
 scalar_t__ SPIFFS_ERR_NOT_READABLE ; 
 int /*<<< orphan*/  SPIFFS_FH_UNOFFS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIFFS_LOCK (int /*<<< orphan*/ *) ; 
 int SPIFFS_O_RDONLY ; 
 scalar_t__ SPIFFS_UNDEFINED_LEN ; 
 int /*<<< orphan*/  SPIFFS_UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ spiffs_fd_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  spiffs_fflush_cache (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spiffs_object_read (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32_t spiffs_hydro_read(spiffs *fs, spiffs_file fh, void *buf, s32_t len) {
  SPIFFS_API_CHECK_CFG(fs);
  SPIFFS_API_CHECK_MOUNT(fs);
  SPIFFS_LOCK(fs);

  spiffs_fd *fd;
  s32_t res;

  fh = SPIFFS_FH_UNOFFS(fs, fh);
  res = spiffs_fd_get(fs, fh, &fd);
  SPIFFS_API_CHECK_RES_UNLOCK(fs, res);

  if ((fd->flags & SPIFFS_O_RDONLY) == 0) {
    res = SPIFFS_ERR_NOT_READABLE;
    SPIFFS_API_CHECK_RES_UNLOCK(fs, res);
  }

  if (fd->size == SPIFFS_UNDEFINED_LEN && len > 0) {
    // special case for zero sized files
    res = SPIFFS_ERR_END_OF_OBJECT;
    SPIFFS_API_CHECK_RES_UNLOCK(fs, res);
  }

#if SPIFFS_CACHE_WR
  spiffs_fflush_cache(fs, fh);
#endif

  if (fd->fdoffset + len >= fd->size) {
    // reading beyond file size
    s32_t avail = fd->size - fd->fdoffset;
    if (avail <= 0) {
      SPIFFS_API_CHECK_RES_UNLOCK(fs, SPIFFS_ERR_END_OF_OBJECT);
    }
    res = spiffs_object_read(fd, fd->fdoffset, avail, (u8_t*)buf);
    if (res == SPIFFS_ERR_END_OF_OBJECT) {
      fd->fdoffset += avail;
      SPIFFS_UNLOCK(fs);
      return avail;
    } else {
      SPIFFS_API_CHECK_RES_UNLOCK(fs, res);
      len = avail;
    }
  } else {
    // reading within file size
    res = spiffs_object_read(fd, fd->fdoffset, len, (u8_t*)buf);
    SPIFFS_API_CHECK_RES_UNLOCK(fs, res);
  }
  fd->fdoffset += len;

  SPIFFS_UNLOCK(fs);

  return len;
}