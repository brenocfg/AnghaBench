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
struct virtual_node {int dummy; } ;
struct virtual_item {int /*<<< orphan*/  vi_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_INDIRECT ; 

__attribute__((used)) static int indirect_create_vi(struct virtual_node *vn,
			      struct virtual_item *vi,
			      int is_affected, int insert_size)
{
	vi->vi_index = TYPE_INDIRECT;
	return 0;
}