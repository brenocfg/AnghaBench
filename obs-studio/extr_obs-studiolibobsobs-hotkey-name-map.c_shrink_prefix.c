#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_4__ {size_t prefix_len; } ;
typedef  TYPE_1__ obs_hotkey_name_map_edge_t ;

/* Variables and functions */
 size_t NAME_MAP_COMPRESS_LENGTH ; 
 int /*<<< orphan*/  bfree (char*) ; 
 char* get_prefix (TYPE_1__*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

__attribute__((used)) static void shrink_prefix(obs_hotkey_name_map_edge_t *e, size_t l)
{
	bool old_comp = e->prefix_len < NAME_MAP_COMPRESS_LENGTH;
	bool new_comp = l < NAME_MAP_COMPRESS_LENGTH;

	char *str = get_prefix(e);

	e->prefix_len = (uint8_t)l;
	if (get_prefix(e) != str)
		strncpy(get_prefix(e), str, l);
	else
		str[l] = 0;

	if (!old_comp && new_comp)
		bfree(str);
}