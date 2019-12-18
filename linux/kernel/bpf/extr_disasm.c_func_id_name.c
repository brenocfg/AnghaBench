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
 int __BPF_FUNC_MAX_ID ; 
 char const** func_id_str ; 

const char *func_id_name(int id)
{
	if (id >= 0 && id < __BPF_FUNC_MAX_ID && func_id_str[id])
		return func_id_str[id];
	else
		return "unknown";
}