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
 int fdt_begin_node (void*,char*) ; 
 int fdt_create (void*,int) ; 
 int fdt_end_node (void*) ; 
 int fdt_finish (void*) ; 
 int fdt_finish_reservemap (void*) ; 
 int fdt_open_into (void*,void*,int) ; 

int fdt_create_empty_tree(void *buf, int bufsize)
{
	int err;

	err = fdt_create(buf, bufsize);
	if (err)
		return err;

	err = fdt_finish_reservemap(buf);
	if (err)
		return err;

	err = fdt_begin_node(buf, "");
	if (err)
		return err;

	err =  fdt_end_node(buf);
	if (err)
		return err;

	err = fdt_finish(buf);
	if (err)
		return err;

	return fdt_open_into(buf, buf, bufsize);
}