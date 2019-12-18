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
struct gengetopt_args_info {int /*<<< orphan*/  pad_orig; int /*<<< orphan*/  reserved2_orig; int /*<<< orphan*/  reserved2_arg; int /*<<< orphan*/  inactive_orig; int /*<<< orphan*/  inactive_arg; int /*<<< orphan*/  second_image_flag_orig; int /*<<< orphan*/  second_image_flag_arg; int /*<<< orphan*/  rsa_signature_orig; int /*<<< orphan*/  rsa_signature_arg; int /*<<< orphan*/  info2_orig; int /*<<< orphan*/  info2_arg; int /*<<< orphan*/  altinfo_orig; int /*<<< orphan*/  altinfo_arg; int /*<<< orphan*/  info1_orig; int /*<<< orphan*/  info1_arg; int /*<<< orphan*/  layoutver_orig; int /*<<< orphan*/  layoutver_arg; int /*<<< orphan*/  entry_orig; int /*<<< orphan*/  entry_arg; int /*<<< orphan*/  load_addr_orig; int /*<<< orphan*/  load_addr_arg; int /*<<< orphan*/  block_size_orig; int /*<<< orphan*/  block_size_arg; int /*<<< orphan*/  signature2_orig; int /*<<< orphan*/  signature2_arg; int /*<<< orphan*/  signature_orig; int /*<<< orphan*/  signature_arg; int /*<<< orphan*/  tag_version_orig; int /*<<< orphan*/  tag_version_arg; int /*<<< orphan*/  image_offset_orig; int /*<<< orphan*/  image_offset_arg; int /*<<< orphan*/  flash_start_orig; int /*<<< orphan*/  flash_start_arg; int /*<<< orphan*/  chipid_orig; int /*<<< orphan*/  chipid_arg; int /*<<< orphan*/  boardid_orig; int /*<<< orphan*/  boardid_arg; int /*<<< orphan*/  cfe_orig; int /*<<< orphan*/  cfe_arg; int /*<<< orphan*/  output_orig; int /*<<< orphan*/  output_arg; int /*<<< orphan*/  rootfs_orig; int /*<<< orphan*/  rootfs_arg; int /*<<< orphan*/  kernel_orig; int /*<<< orphan*/  kernel_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_given (struct gengetopt_args_info*) ; 
 int /*<<< orphan*/  free_string_field (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
imagetag_cmdline_release (struct gengetopt_args_info *args_info)
{

  free_string_field (&(args_info->kernel_arg));
  free_string_field (&(args_info->kernel_orig));
  free_string_field (&(args_info->rootfs_arg));
  free_string_field (&(args_info->rootfs_orig));
  free_string_field (&(args_info->output_arg));
  free_string_field (&(args_info->output_orig));
  free_string_field (&(args_info->cfe_arg));
  free_string_field (&(args_info->cfe_orig));
  free_string_field (&(args_info->boardid_arg));
  free_string_field (&(args_info->boardid_orig));
  free_string_field (&(args_info->chipid_arg));
  free_string_field (&(args_info->chipid_orig));
  free_string_field (&(args_info->flash_start_arg));
  free_string_field (&(args_info->flash_start_orig));
  free_string_field (&(args_info->image_offset_arg));
  free_string_field (&(args_info->image_offset_orig));
  free_string_field (&(args_info->tag_version_arg));
  free_string_field (&(args_info->tag_version_orig));
  free_string_field (&(args_info->signature_arg));
  free_string_field (&(args_info->signature_orig));
  free_string_field (&(args_info->signature2_arg));
  free_string_field (&(args_info->signature2_orig));
  free_string_field (&(args_info->block_size_arg));
  free_string_field (&(args_info->block_size_orig));
  free_string_field (&(args_info->load_addr_arg));
  free_string_field (&(args_info->load_addr_orig));
  free_string_field (&(args_info->entry_arg));
  free_string_field (&(args_info->entry_orig));
  free_string_field (&(args_info->layoutver_arg));
  free_string_field (&(args_info->layoutver_orig));
  free_string_field (&(args_info->info1_arg));
  free_string_field (&(args_info->info1_orig));
  free_string_field (&(args_info->altinfo_arg));
  free_string_field (&(args_info->altinfo_orig));
  free_string_field (&(args_info->info2_arg));
  free_string_field (&(args_info->info2_orig));
  free_string_field (&(args_info->rsa_signature_arg));
  free_string_field (&(args_info->rsa_signature_orig));
  free_string_field (&(args_info->second_image_flag_arg));
  free_string_field (&(args_info->second_image_flag_orig));
  free_string_field (&(args_info->inactive_arg));
  free_string_field (&(args_info->inactive_orig));
  free_string_field (&(args_info->reserved2_arg));
  free_string_field (&(args_info->reserved2_orig));
  free_string_field (&(args_info->pad_orig));
  
  

  clear_given (args_info);
}