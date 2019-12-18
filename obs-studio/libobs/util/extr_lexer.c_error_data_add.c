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
typedef  void* uint32_t ;
struct error_item {char const* file; int level; int /*<<< orphan*/  error; void* column; void* row; } ;
struct error_data {int /*<<< orphan*/  errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  bstrdup (char const*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct error_item*) ; 

void error_data_add(struct error_data *data, const char *file, uint32_t row,
		    uint32_t column, const char *msg, int level)
{
	struct error_item item;

	if (!data)
		return;

	item.file = file;
	item.row = row;
	item.column = column;
	item.level = level;
	item.error = bstrdup(msg);

	da_push_back(data->errors, &item);
}