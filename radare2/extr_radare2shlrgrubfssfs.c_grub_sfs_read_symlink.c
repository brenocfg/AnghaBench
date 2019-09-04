#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct grub_sfs_data {int /*<<< orphan*/  blocksize; int /*<<< orphan*/  disk; } ;
typedef  TYPE_1__* grub_fshelp_node_t ;
struct TYPE_3__ {int /*<<< orphan*/  block; struct grub_sfs_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_disk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_free (char*) ; 
 char* grub_malloc (int /*<<< orphan*/ ) ; 
 char* grub_strdup (char*) ; 

__attribute__((used)) static char *
grub_sfs_read_symlink (grub_fshelp_node_t node)
{
  struct grub_sfs_data *data = node->data;
  char *symlink;
  char *block;

  block = grub_malloc (data->blocksize);
  if (!block)
    return 0;

  grub_disk_read (data->disk, node->block, 0, data->blocksize, block);
  if (grub_errno)
    {
      grub_free (block);
      return 0;
    }

  /* This is just a wild guess, but it always worked for me.  How the
     SLNK block looks like is not documented in the SFS docs.  */
  symlink = grub_strdup (&block[24]);
  grub_free (block);
  if (!symlink)
    return 0;

  return symlink;
}