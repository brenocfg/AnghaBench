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
struct super_block {int dummy; } ;
struct buffer_info {int /*<<< orphan*/  tb; } ;

/* Variables and functions */
 struct super_block* sb_from_tb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct super_block *sb_from_bi(struct buffer_info *bi)
{
	return bi ? sb_from_tb(bi->tb) : NULL;
}