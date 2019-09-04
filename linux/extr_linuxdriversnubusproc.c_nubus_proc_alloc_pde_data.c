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
struct nubus_proc_pde_data {unsigned char* res_ptr; unsigned int res_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nubus_proc_pde_data* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nubus_proc_pde_data *
nubus_proc_alloc_pde_data(unsigned char *ptr, unsigned int size)
{
	struct nubus_proc_pde_data *pde_data;

	pde_data = kmalloc(sizeof(*pde_data), GFP_KERNEL);
	if (!pde_data)
		return NULL;

	pde_data->res_ptr = ptr;
	pde_data->res_size = size;
	return pde_data;
}