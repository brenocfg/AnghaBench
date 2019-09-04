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
struct noise_gate_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct noise_gate_data*) ; 

__attribute__((used)) static void noise_gate_destroy(void *data)
{
	struct noise_gate_data *ng = data;
	bfree(ng);
}