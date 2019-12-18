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
typedef  int /*<<< orphan*/  uint32_t ;
struct vfs_file {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_FILE_FH (struct vfs_file const*) ; 
 int /*<<< orphan*/  SPIFFS_SEEK_END ; 
 int /*<<< orphan*/  SPIFFS_SEEK_SET ; 
 int /*<<< orphan*/  SPIFFS_lseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIFFS_tell (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh ; 
 int /*<<< orphan*/  fs ; 

__attribute__((used)) static uint32_t myspiffs_vfs_size( const struct vfs_file *fd ) {
  GET_FILE_FH(fd);

  int32_t curpos = SPIFFS_tell( &fs, fh );
  int32_t size = SPIFFS_lseek( &fs, fh, 0, SPIFFS_SEEK_END );
  (void) SPIFFS_lseek( &fs, fh, curpos, SPIFFS_SEEK_SET );

   return size;
}