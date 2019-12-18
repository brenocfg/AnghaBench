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
struct grub_file {int dummy; } ;
typedef  int /*<<< orphan*/  grub_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_NOT_IMPLEMENTED_YET ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static grub_err_t
grub_btrfs_open (struct grub_file *file ,
		 const char *name )
{
  return grub_error (GRUB_ERR_NOT_IMPLEMENTED_YET, "only detection is supported for Btrfs");
}