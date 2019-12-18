#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_1__* s_export_op; } ;
struct TYPE_2__ {scalar_t__ encode_fh; int /*<<< orphan*/  fh_to_dentry; } ;

/* Variables and functions */
 int FILEID_INO32_GEN ; 

int ovl_can_decode_fh(struct super_block *sb)
{
	if (!sb->s_export_op || !sb->s_export_op->fh_to_dentry)
		return 0;

	return sb->s_export_op->encode_fh ? -1 : FILEID_INO32_GEN;
}