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
struct gain_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct gain_data*) ; 

__attribute__((used)) static void gain_destroy(void *data)
{
	struct gain_data *gf = data;
	bfree(gf);
}