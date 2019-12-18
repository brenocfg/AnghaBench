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
struct tipc_media {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct tipc_media** media_info_array ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

struct tipc_media *tipc_media_find(const char *name)
{
	u32 i;

	for (i = 0; media_info_array[i] != NULL; i++) {
		if (!strcmp(media_info_array[i]->name, name))
			break;
	}
	return media_info_array[i];
}