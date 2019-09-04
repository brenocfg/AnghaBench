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
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_data_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_data_create () ; 

__attribute__((used)) static inline obs_data_t *obs_data_newref(obs_data_t *data)
{
	if (data)
		obs_data_addref(data);
	else
		data = obs_data_create();

	return data;
}