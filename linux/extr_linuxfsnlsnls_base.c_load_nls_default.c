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
struct nls_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_NLS_DEFAULT ; 
 struct nls_table default_table ; 
 struct nls_table* load_nls (int /*<<< orphan*/ ) ; 

struct nls_table *load_nls_default(void)
{
	struct nls_table *default_nls;
	
	default_nls = load_nls(CONFIG_NLS_DEFAULT);
	if (default_nls != NULL)
		return default_nls;
	else
		return &default_table;
}