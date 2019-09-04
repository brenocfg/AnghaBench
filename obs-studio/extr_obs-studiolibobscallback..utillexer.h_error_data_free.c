#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  num; int /*<<< orphan*/  array; } ;
struct error_data {TYPE_1__ errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  error_item_array_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void error_data_free(struct error_data *data)
{
	error_item_array_free(data->errors.array, data->errors.num);
	da_free(data->errors);
}