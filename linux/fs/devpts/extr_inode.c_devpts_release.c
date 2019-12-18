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
struct pts_fs_info {int /*<<< orphan*/  sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  deactivate_super (int /*<<< orphan*/ ) ; 

void devpts_release(struct pts_fs_info *fsi)
{
	deactivate_super(fsi->sb);
}