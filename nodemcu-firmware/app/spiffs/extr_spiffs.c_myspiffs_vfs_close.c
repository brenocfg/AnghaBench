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
struct vfs_file {int dummy; } ;
typedef  int /*<<< orphan*/  sint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_FILE_FH (struct vfs_file const*) ; 
 int /*<<< orphan*/  SPIFFS_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  fs ; 

__attribute__((used)) static sint32_t myspiffs_vfs_close( const struct vfs_file *fd ) {
  GET_FILE_FH(fd);

  sint32_t res = SPIFFS_close( &fs, fh );

  // free descriptor memory
  free( (void *)fd );

  return res;
}