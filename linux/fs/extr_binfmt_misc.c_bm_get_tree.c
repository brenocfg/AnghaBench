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
struct fs_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bm_fill_super ; 
 int get_tree_single (struct fs_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bm_get_tree(struct fs_context *fc)
{
	return get_tree_single(fc, bm_fill_super);
}