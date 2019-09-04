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
struct editable_list_data {int /*<<< orphan*/  filter; int /*<<< orphan*/  default_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void editable_list_data_free(struct editable_list_data *data)
{
	bfree(data->default_path);
	bfree(data->filter);
}