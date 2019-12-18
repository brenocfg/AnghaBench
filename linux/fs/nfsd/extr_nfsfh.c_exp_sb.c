#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct svc_export {TYPE_2__ ex_path; } ;
struct super_block {int dummy; } ;
struct TYPE_3__ {struct super_block* d_sb; } ;

/* Variables and functions */

__attribute__((used)) static struct super_block *exp_sb(struct svc_export *exp)
{
	return exp->ex_path.dentry->d_sb;
}