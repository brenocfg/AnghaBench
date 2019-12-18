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

/* Variables and functions */
 int memcmp (void const*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (size_t,size_t) ; 

__attribute__((used)) static int compare_names(const void *name1, size_t name1_len,
			 const void *name2, size_t name2_len)
{
	int ret;

	ret = memcmp(name1, name2, min(name1_len, name2_len));
	if (!ret) {
		if (name1_len < name2_len)
			ret = -1;
		else if (name1_len > name2_len)
			ret = 1;
	}
	return ret;
}