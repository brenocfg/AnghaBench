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
struct TYPE_3__ {scalar_t__ prefix_len; char* prefix; char* compressed_prefix; } ;
typedef  TYPE_1__ obs_hotkey_name_map_edge_t ;

/* Variables and functions */
 scalar_t__ NAME_MAP_COMPRESS_LENGTH ; 

__attribute__((used)) static inline char *get_prefix(obs_hotkey_name_map_edge_t *e)
{
	return e->prefix_len >= NAME_MAP_COMPRESS_LENGTH ?
		e->prefix : e->compressed_prefix;
}