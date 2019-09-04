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
struct hist_elt_data {scalar_t__ comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  save_comm (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hist_trigger_elt_data_init(struct tracing_map_elt *elt)
{
	struct hist_elt_data *elt_data = elt->private_data;

	if (elt_data->comm)
		save_comm(elt_data->comm, current);
}