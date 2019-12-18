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
typedef  int /*<<< orphan*/  PathKey ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pk_eclass ; 
 int /*<<< orphan*/  pk_nulls_first ; 
 int /*<<< orphan*/  pk_opfamily ; 
 int /*<<< orphan*/  pk_strategy ; 

__attribute__((used)) static bool
_equalPathKey(const PathKey *a, const PathKey *b)
{
	/* We assume pointer equality is sufficient to compare the eclasses */
	COMPARE_SCALAR_FIELD(pk_eclass);
	COMPARE_SCALAR_FIELD(pk_opfamily);
	COMPARE_SCALAR_FIELD(pk_strategy);
	COMPARE_SCALAR_FIELD(pk_nulls_first);

	return true;
}