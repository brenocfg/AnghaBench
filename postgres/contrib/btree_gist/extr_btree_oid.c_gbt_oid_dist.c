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
typedef  int /*<<< orphan*/  float8 ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */

__attribute__((used)) static float8
gbt_oid_dist(const void *a, const void *b, FmgrInfo *flinfo)
{
	Oid			aa = *(const Oid *) a;
	Oid			bb = *(const Oid *) b;

	if (aa < bb)
		return (float8) (bb - aa);
	else
		return (float8) (aa - bb);
}