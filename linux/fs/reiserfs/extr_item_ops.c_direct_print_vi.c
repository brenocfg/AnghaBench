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
struct virtual_item {int /*<<< orphan*/  vi_ih; int /*<<< orphan*/  vi_type; int /*<<< orphan*/  vi_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  reiserfs_warning (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void direct_print_vi(struct virtual_item *vi)
{
	reiserfs_warning(NULL, "reiserfs-16101",
			 "DIRECT, index %d, type 0x%x, %h",
			 vi->vi_index, vi->vi_type, vi->vi_ih);
}