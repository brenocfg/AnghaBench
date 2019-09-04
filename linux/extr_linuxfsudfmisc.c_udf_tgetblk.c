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
typedef  int /*<<< orphan*/  udf_pblk_t ;
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDF_FLAG_VARCONV ; 
 scalar_t__ UDF_QUERY_FLAG (struct super_block*,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_getblk (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_fixed_to_variable (int /*<<< orphan*/ ) ; 

struct buffer_head *udf_tgetblk(struct super_block *sb, udf_pblk_t block)
{
	if (UDF_QUERY_FLAG(sb, UDF_FLAG_VARCONV))
		return sb_getblk(sb, udf_fixed_to_variable(block));
	else
		return sb_getblk(sb, block);
}