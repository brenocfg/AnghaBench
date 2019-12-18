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
typedef  int /*<<< orphan*/  umode_t ;
typedef  int /*<<< orphan*/  u32 ;
struct dentry {int dummy; } ;
struct array_data {int /*<<< orphan*/  elements; int /*<<< orphan*/ * array; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  debugfs_create_file_unsafe (char const*,int /*<<< orphan*/ ,struct dentry*,struct array_data*,int /*<<< orphan*/ *) ; 
 struct array_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32_array_fops ; 

void debugfs_create_u32_array(const char *name, umode_t mode,
			      struct dentry *parent, u32 *array, u32 elements)
{
	struct array_data *data = kmalloc(sizeof(*data), GFP_KERNEL);

	if (data == NULL)
		return;

	data->array = array;
	data->elements = elements;

	debugfs_create_file_unsafe(name, mode, parent, data, &u32_array_fops);
}