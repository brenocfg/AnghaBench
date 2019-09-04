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
typedef  int u8 ;
typedef  scalar_t__ (* toupper_t ) (int /*<<< orphan*/ ) ;
struct TYPE_2__ {int* name; int len; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int AFFSNAMEMAX ; 

__attribute__((used)) static inline int
affs_match(struct dentry *dentry, const u8 *name2, toupper_t toupper)
{
	const u8 *name = dentry->d_name.name;
	int len = dentry->d_name.len;

	if (len >= AFFSNAMEMAX) {
		if (*name2 < AFFSNAMEMAX)
			return 0;
		len = AFFSNAMEMAX;
	} else if (len != *name2)
		return 0;

	for (name2++; len > 0; len--)
		if (toupper(*name++) != toupper(*name2++))
			return 0;
	return 1;
}