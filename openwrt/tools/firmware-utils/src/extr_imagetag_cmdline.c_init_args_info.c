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
struct gengetopt_args_info {void* align_rootfs_help; void* pad_help; void* kernel_file_has_header_help; void* reserved2_help; void* inactive_help; void* second_image_flag_help; void* rsa_signature_help; void* root_first_help; void* info2_help; void* altinfo_help; void* info1_help; void* layoutver_help; void* entry_help; void* load_addr_help; void* block_size_help; void* signature2_help; void* signature_help; void* tag_version_help; void* image_offset_help; void* flash_start_help; void* chipid_help; void* boardid_help; void* cfe_help; void* output_help; void* rootfs_help; void* kernel_help; void* version_help; void* help_help; } ;

/* Variables and functions */
 void** gengetopt_args_info_help ; 

__attribute__((used)) static
void init_args_info(struct gengetopt_args_info *args_info)
{


  args_info->help_help = gengetopt_args_info_help[0] ;
  args_info->version_help = gengetopt_args_info_help[1] ;
  args_info->kernel_help = gengetopt_args_info_help[2] ;
  args_info->rootfs_help = gengetopt_args_info_help[3] ;
  args_info->output_help = gengetopt_args_info_help[4] ;
  args_info->cfe_help = gengetopt_args_info_help[5] ;
  args_info->boardid_help = gengetopt_args_info_help[6] ;
  args_info->chipid_help = gengetopt_args_info_help[7] ;
  args_info->flash_start_help = gengetopt_args_info_help[8] ;
  args_info->image_offset_help = gengetopt_args_info_help[9] ;
  args_info->tag_version_help = gengetopt_args_info_help[10] ;
  args_info->signature_help = gengetopt_args_info_help[11] ;
  args_info->signature2_help = gengetopt_args_info_help[12] ;
  args_info->block_size_help = gengetopt_args_info_help[13] ;
  args_info->load_addr_help = gengetopt_args_info_help[14] ;
  args_info->entry_help = gengetopt_args_info_help[15] ;
  args_info->layoutver_help = gengetopt_args_info_help[16] ;
  args_info->info1_help = gengetopt_args_info_help[17] ;
  args_info->altinfo_help = gengetopt_args_info_help[18] ;
  args_info->info2_help = gengetopt_args_info_help[19] ;
  args_info->root_first_help = gengetopt_args_info_help[20] ;
  args_info->rsa_signature_help = gengetopt_args_info_help[21] ;
  args_info->second_image_flag_help = gengetopt_args_info_help[22] ;
  args_info->inactive_help = gengetopt_args_info_help[23] ;
  args_info->reserved2_help = gengetopt_args_info_help[24] ;
  args_info->kernel_file_has_header_help = gengetopt_args_info_help[25] ;
  args_info->pad_help = gengetopt_args_info_help[26] ;
  args_info->align_rootfs_help = gengetopt_args_info_help[27] ;
  
}