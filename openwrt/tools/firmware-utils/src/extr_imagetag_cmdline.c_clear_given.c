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
struct gengetopt_args_info {scalar_t__ align_rootfs_given; scalar_t__ pad_given; scalar_t__ kernel_file_has_header_given; scalar_t__ reserved2_given; scalar_t__ inactive_given; scalar_t__ second_image_flag_given; scalar_t__ rsa_signature_given; scalar_t__ root_first_given; scalar_t__ info2_given; scalar_t__ altinfo_given; scalar_t__ info1_given; scalar_t__ layoutver_given; scalar_t__ entry_given; scalar_t__ load_addr_given; scalar_t__ block_size_given; scalar_t__ signature2_given; scalar_t__ signature_given; scalar_t__ tag_version_given; scalar_t__ image_offset_given; scalar_t__ flash_start_given; scalar_t__ chipid_given; scalar_t__ boardid_given; scalar_t__ cfe_given; scalar_t__ output_given; scalar_t__ rootfs_given; scalar_t__ kernel_given; scalar_t__ version_given; scalar_t__ help_given; } ;

/* Variables and functions */

__attribute__((used)) static
void clear_given (struct gengetopt_args_info *args_info)
{
  args_info->help_given = 0 ;
  args_info->version_given = 0 ;
  args_info->kernel_given = 0 ;
  args_info->rootfs_given = 0 ;
  args_info->output_given = 0 ;
  args_info->cfe_given = 0 ;
  args_info->boardid_given = 0 ;
  args_info->chipid_given = 0 ;
  args_info->flash_start_given = 0 ;
  args_info->image_offset_given = 0 ;
  args_info->tag_version_given = 0 ;
  args_info->signature_given = 0 ;
  args_info->signature2_given = 0 ;
  args_info->block_size_given = 0 ;
  args_info->load_addr_given = 0 ;
  args_info->entry_given = 0 ;
  args_info->layoutver_given = 0 ;
  args_info->info1_given = 0 ;
  args_info->altinfo_given = 0 ;
  args_info->info2_given = 0 ;
  args_info->root_first_given = 0 ;
  args_info->rsa_signature_given = 0 ;
  args_info->second_image_flag_given = 0 ;
  args_info->inactive_given = 0 ;
  args_info->reserved2_given = 0 ;
  args_info->kernel_file_has_header_given = 0 ;
  args_info->pad_given = 0 ;
  args_info->align_rootfs_given = 0 ;
}