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
struct kstat {int /*<<< orphan*/  size; } ;
struct iattr {int /*<<< orphan*/  ia_size; int /*<<< orphan*/  ia_valid; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_SIZE ; 
 int notify_change (struct dentry*,struct iattr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ovl_set_size(struct dentry *upperdentry, struct kstat *stat)
{
	struct iattr attr = {
		.ia_valid = ATTR_SIZE,
		.ia_size = stat->size,
	};

	return notify_change(upperdentry, &attr, NULL);
}