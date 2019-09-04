#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int ccid_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__**) ; 
 int ENOBUFS ; 
 TYPE_1__** ccids ; 
 int /*<<< orphan*/  gfp_any () ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 

int ccid_get_builtin_ccids(u8 **ccid_array, u8 *array_len)
{
	*ccid_array = kmalloc(ARRAY_SIZE(ccids), gfp_any());
	if (*ccid_array == NULL)
		return -ENOBUFS;

	for (*array_len = 0; *array_len < ARRAY_SIZE(ccids); *array_len += 1)
		(*ccid_array)[*array_len] = ccids[*array_len]->ccid_id;
	return 0;
}