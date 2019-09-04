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
typedef  size_t u32 ;
struct kernfs_iattrs {size_t ia_secdata_len; void* ia_secdata; } ;

/* Variables and functions */

__attribute__((used)) static int kernfs_node_setsecdata(struct kernfs_iattrs *attrs, void **secdata,
				  u32 *secdata_len)
{
	void *old_secdata;
	size_t old_secdata_len;

	old_secdata = attrs->ia_secdata;
	old_secdata_len = attrs->ia_secdata_len;

	attrs->ia_secdata = *secdata;
	attrs->ia_secdata_len = *secdata_len;

	*secdata = old_secdata;
	*secdata_len = old_secdata_len;
	return 0;
}