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
struct db_export {int /*<<< orphan*/ * crp; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_return_processor__free (int /*<<< orphan*/ *) ; 

void db_export__exit(struct db_export *dbe)
{
	call_return_processor__free(dbe->crp);
	dbe->crp = NULL;
}