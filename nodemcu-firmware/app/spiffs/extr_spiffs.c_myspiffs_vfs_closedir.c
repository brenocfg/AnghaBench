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
struct vfs_dir {int dummy; } ;
typedef  int /*<<< orphan*/  sint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_DIR_D (struct vfs_dir const*) ; 
 int /*<<< orphan*/  SPIFFS_closedir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d ; 
 int /*<<< orphan*/  free (void*) ; 

__attribute__((used)) static sint32_t myspiffs_vfs_closedir( const struct vfs_dir *dd ) {
  GET_DIR_D(dd);

  sint32_t res = SPIFFS_closedir( d );

  // free descriptor memory
  free( (void *)dd );
}