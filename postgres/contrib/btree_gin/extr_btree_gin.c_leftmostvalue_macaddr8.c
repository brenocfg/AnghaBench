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
typedef  int /*<<< orphan*/  macaddr8 ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Macaddr8PGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * palloc0 (int) ; 

__attribute__((used)) static Datum
leftmostvalue_macaddr8(void)
{
	macaddr8   *v = palloc0(sizeof(macaddr8));

	return Macaddr8PGetDatum(v);
}