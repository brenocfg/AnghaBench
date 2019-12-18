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
struct super_block {scalar_t__ s_bdev; } ;
struct fs_context {scalar_t__ sget_key; } ;

/* Variables and functions */

__attribute__((used)) static int test_meta_super(struct super_block *s, struct fs_context *fc)
{
	return (fc->sget_key == s->s_bdev);
}