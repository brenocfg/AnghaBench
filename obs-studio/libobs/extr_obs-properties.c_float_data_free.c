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
struct float_data {scalar_t__ suffix; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (scalar_t__) ; 

__attribute__((used)) static inline void float_data_free(struct float_data *data)
{
	if (data->suffix)
		bfree(data->suffix);
}