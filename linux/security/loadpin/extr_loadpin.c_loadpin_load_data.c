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
typedef  enum kernel_read_file_id { ____Placeholder_kernel_read_file_id } kernel_read_file_id ;
typedef  enum kernel_load_data_id { ____Placeholder_kernel_load_data_id } kernel_load_data_id ;

/* Variables and functions */
 int loadpin_read_file (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int loadpin_load_data(enum kernel_load_data_id id)
{
	return loadpin_read_file(NULL, (enum kernel_read_file_id) id);
}