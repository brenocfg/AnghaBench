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
typedef  int /*<<< orphan*/  u32 ;
struct tb_property_rootdir_entry {scalar_t__ magic; size_t length; } ;
struct tb_property_dir {int dummy; } ;

/* Variables and functions */
 scalar_t__ TB_PROPERTY_ROOTDIR_MAGIC ; 
 struct tb_property_dir* __tb_property_parse_dir (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,size_t,int) ; 

struct tb_property_dir *tb_property_parse_dir(const u32 *block,
					      size_t block_len)
{
	const struct tb_property_rootdir_entry *rootdir =
		(const struct tb_property_rootdir_entry *)block;

	if (rootdir->magic != TB_PROPERTY_ROOTDIR_MAGIC)
		return NULL;
	if (rootdir->length > block_len)
		return NULL;

	return __tb_property_parse_dir(block, block_len, 0, rootdir->length,
				       true);
}