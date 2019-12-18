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
struct grub_jfs_diropen {struct grub_jfs_diropen* dirpage; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_free (struct grub_jfs_diropen*) ; 

__attribute__((used)) static void
grub_jfs_closedir (struct grub_jfs_diropen *diro)
{
  if (!diro)
    return;
  grub_free (diro->dirpage);
  grub_free (diro);
}