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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FR_OK ; 
 int /*<<< orphan*/  GET_FIL_FP (struct vfs_file const*) ; 
 int /*<<< orphan*/  f_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fp ; 
 int /*<<< orphan*/  last_result ; 

__attribute__((used)) static int32_t myfatfs_tell( const struct vfs_file *fd )
{
  GET_FIL_FP(fd);

  last_result = FR_OK;

  return f_tell( fp );
}