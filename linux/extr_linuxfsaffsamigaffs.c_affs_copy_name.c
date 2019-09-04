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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFFSNAMEMAX ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
affs_copy_name(unsigned char *bstr, struct dentry *dentry)
{
	u32 len = min(dentry->d_name.len, AFFSNAMEMAX);

	*bstr++ = len;
	memcpy(bstr, dentry->d_name.name, len);
	return len;
}