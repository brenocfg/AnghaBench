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
typedef  int spiffs_file ;
struct TYPE_5__ {scalar_t__ file_nbr; } ;
typedef  TYPE_1__ spiffs_fd ;
struct TYPE_6__ {scalar_t__ fd_space; scalar_t__ fd_count; } ;
typedef  TYPE_2__ spiffs ;
typedef  int /*<<< orphan*/  s32_t ;
typedef  int s16_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_ERR_BAD_DESCRIPTOR ; 
 int /*<<< orphan*/  SPIFFS_ERR_FILE_CLOSED ; 
 int /*<<< orphan*/  SPIFFS_OK ; 

s32_t spiffs_fd_get(spiffs *fs, spiffs_file f, spiffs_fd **fd) {
  if (f <= 0 || f > (s16_t)fs->fd_count) {
    return SPIFFS_ERR_BAD_DESCRIPTOR;
  }
  spiffs_fd *fds = (spiffs_fd *)fs->fd_space;
  *fd = &fds[f-1];
  if ((*fd)->file_nbr == 0) {
    return SPIFFS_ERR_FILE_CLOSED;
  }
  return SPIFFS_OK;
}