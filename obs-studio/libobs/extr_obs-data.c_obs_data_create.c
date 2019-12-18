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
struct obs_data {int ref; } ;
typedef  struct obs_data obs_data_t ;

/* Variables and functions */
 struct obs_data* bzalloc (int) ; 

obs_data_t *obs_data_create()
{
	struct obs_data *data = bzalloc(sizeof(struct obs_data));
	data->ref = 1;

	return data;
}