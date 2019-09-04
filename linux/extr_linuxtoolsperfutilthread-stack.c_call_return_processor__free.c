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
struct call_return_processor {int /*<<< orphan*/  cpr; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_path_root__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct call_return_processor*) ; 

void call_return_processor__free(struct call_return_processor *crp)
{
	if (crp) {
		call_path_root__free(crp->cpr);
		free(crp);
	}
}