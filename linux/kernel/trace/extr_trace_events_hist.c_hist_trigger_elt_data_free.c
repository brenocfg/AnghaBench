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
struct tracing_map_elt {struct hist_elt_data* private_data; } ;
struct hist_elt_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hist_elt_data_free (struct hist_elt_data*) ; 

__attribute__((used)) static void hist_trigger_elt_data_free(struct tracing_map_elt *elt)
{
	struct hist_elt_data *elt_data = elt->private_data;

	hist_elt_data_free(elt_data);
}