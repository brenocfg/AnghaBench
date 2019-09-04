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
struct nlm_block {TYPE_1__* b_file; int /*<<< orphan*/  b_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  f_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put_mutex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlmsvc_free_block ; 

__attribute__((used)) static void nlmsvc_release_block(struct nlm_block *block)
{
	if (block != NULL)
		kref_put_mutex(&block->b_count, nlmsvc_free_block, &block->b_file->f_mutex);
}