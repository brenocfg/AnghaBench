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
typedef  int /*<<< orphan*/  vfs_vol ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ myspiffs_mount (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vfs_vol  *myspiffs_vfs_mount( const char *name, int num ) {
  // volume descriptor not supported, just return TRUE / FALSE
  return myspiffs_mount(FALSE) ? (vfs_vol *)1 : NULL;
}