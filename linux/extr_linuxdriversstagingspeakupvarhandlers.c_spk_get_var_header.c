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
struct st_var_header {int /*<<< orphan*/  data; } ;
typedef  enum var_id_t { ____Placeholder_var_id_t } var_id_t ;

/* Variables and functions */
 int MAXVARS ; 
 struct st_var_header** var_ptrs ; 

struct st_var_header *spk_get_var_header(enum var_id_t var_id)
{
	struct st_var_header *p_header;

	if (var_id < 0 || var_id >= MAXVARS)
		return NULL;
	p_header = var_ptrs[var_id];
	if (!p_header->data)
		return NULL;
	return p_header;
}