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
struct expander_data {size_t env_in_len; int /*<<< orphan*/  env_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  brealloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void resize_env_in_buffer(struct expander_data *cd, size_t len)
{
	cd->env_in_len = len;
	cd->env_in = brealloc(cd->env_in, cd->env_in_len * sizeof(float));
}