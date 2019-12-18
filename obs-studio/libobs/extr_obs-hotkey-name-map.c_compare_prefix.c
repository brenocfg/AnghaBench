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
typedef  enum obs_hotkey_name_map_edge_compare_result { ____Placeholder_obs_hotkey_name_map_edge_compare_result } obs_hotkey_name_map_edge_compare_result ;

/* Variables and functions */
 int RES_COMMON_PREFIX ; 
 int RES_MATCHES ; 
 int RES_NO_MATCH ; 
 int RES_PREFIX_MATCHES ; 
 char* get_prefix (TYPE_1__*) ; 

__attribute__((used)) static enum obs_hotkey_name_map_edge_compare_result
compare_prefix(obs_hotkey_name_map_edge_t *edge, const char *key, size_t l)
{
	uint8_t pref_len = edge->prefix_len;
	const char *str = get_prefix(edge);
	size_t i = 0;

	for (; i < l && i < pref_len; i++)
		if (str[i] != key[i])
			break;

	if (i != 0 && pref_len == i)
		return l == i ? RES_MATCHES : RES_PREFIX_MATCHES;
	if (i != 0)
		return pref_len == i ? RES_PREFIX_MATCHES : RES_COMMON_PREFIX;
	return RES_NO_MATCH;
}