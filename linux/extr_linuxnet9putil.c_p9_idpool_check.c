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
struct p9_idpool {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/ * idr_find (int /*<<< orphan*/ *,int) ; 

int p9_idpool_check(int id, struct p9_idpool *p)
{
	return idr_find(&p->pool, id) != NULL;
}