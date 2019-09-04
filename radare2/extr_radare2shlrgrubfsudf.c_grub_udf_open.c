#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct grub_udf_data {int /*<<< orphan*/  root_icb; } ;
struct TYPE_3__ {int /*<<< orphan*/  file_size; } ;
struct grub_fshelp_node {TYPE_1__ fe; } ;
struct grub_file {int /*<<< orphan*/  size; scalar_t__ offset; struct grub_fshelp_node* data; TYPE_2__* device; } ;
typedef  int /*<<< orphan*/  grub_err_t ;
struct TYPE_4__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_FSHELP_REG ; 
 int /*<<< orphan*/  U64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_dl_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_dl_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_free (struct grub_udf_data*) ; 
 scalar_t__ grub_fshelp_find_file (char const*,struct grub_fshelp_node*,struct grub_fshelp_node**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_udf_iterate_dir ; 
 struct grub_udf_data* grub_udf_mount (int /*<<< orphan*/ ) ; 
 scalar_t__ grub_udf_read_icb (struct grub_udf_data*,int /*<<< orphan*/ *,struct grub_fshelp_node*) ; 
 int /*<<< orphan*/  my_mod ; 

__attribute__((used)) static grub_err_t
grub_udf_open (struct grub_file *file, const char *name)
{
  struct grub_udf_data *data;
  struct grub_fshelp_node rootnode;
  struct grub_fshelp_node *foundnode;

  grub_dl_ref (my_mod);

  data = grub_udf_mount (file->device->disk);
  if (!data)
    goto fail;

  if (grub_udf_read_icb (data, &data->root_icb, &rootnode))
    goto fail;

  if (grub_fshelp_find_file (name, &rootnode,
			     &foundnode,
			     grub_udf_iterate_dir, 0, 0, GRUB_FSHELP_REG))
    goto fail;

  file->data = foundnode;
  file->offset = 0;
  file->size = U64 (foundnode->fe.file_size);

  return 0;

fail:
  grub_dl_unref (my_mod);

  grub_free (data);

  return grub_errno;
}