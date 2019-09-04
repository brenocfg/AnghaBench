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
struct intel_bts_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct intel_bts_queue*) ; 

__attribute__((used)) static void intel_bts_free_queue(void *priv)
{
	struct intel_bts_queue *btsq = priv;

	if (!btsq)
		return;
	free(btsq);
}