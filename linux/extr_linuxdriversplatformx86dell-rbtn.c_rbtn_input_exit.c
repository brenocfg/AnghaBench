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
struct rbtn_data {int /*<<< orphan*/ * input_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbtn_input_exit(struct rbtn_data *rbtn_data)
{
	input_unregister_device(rbtn_data->input_dev);
	rbtn_data->input_dev = NULL;
}