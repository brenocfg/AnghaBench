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
struct sparsebit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sparsebit*) ; 
 int /*<<< orphan*/  sparsebit_clear_all (struct sparsebit*) ; 

void sparsebit_free(struct sparsebit **sbitp)
{
	struct sparsebit *s = *sbitp;

	if (!s)
		return;

	sparsebit_clear_all(s);
	free(s);
	*sbitp = NULL;
}