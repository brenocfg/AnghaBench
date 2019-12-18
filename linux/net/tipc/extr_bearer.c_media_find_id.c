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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct tipc_media {scalar_t__ type_id; } ;

/* Variables and functions */
 struct tipc_media** media_info_array ; 

__attribute__((used)) static struct tipc_media *media_find_id(u8 type)
{
	u32 i;

	for (i = 0; media_info_array[i] != NULL; i++) {
		if (media_info_array[i]->type_id == type)
			break;
	}
	return media_info_array[i];
}