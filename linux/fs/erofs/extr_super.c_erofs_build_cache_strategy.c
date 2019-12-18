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
typedef  int /*<<< orphan*/  substring_t ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  erofs_info (struct super_block*,char*) ; 

__attribute__((used)) static int erofs_build_cache_strategy(struct super_block *sb,
				      substring_t *args)
{
	erofs_info(sb, "EROFS compression is disabled, so cache strategy is ignored");
	return 0;
}