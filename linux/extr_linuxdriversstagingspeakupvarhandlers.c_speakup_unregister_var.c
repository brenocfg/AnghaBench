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
struct st_var_header {int /*<<< orphan*/ * data; } ;
typedef  enum var_id_t { ____Placeholder_var_id_t } var_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MAXVARS ; 
 struct st_var_header** var_ptrs ; 

void speakup_unregister_var(enum var_id_t var_id)
{
	struct st_var_header *p_header;

	BUG_ON(var_id < 0 || var_id >= MAXVARS);
	p_header = var_ptrs[var_id];
	p_header->data = NULL;
}