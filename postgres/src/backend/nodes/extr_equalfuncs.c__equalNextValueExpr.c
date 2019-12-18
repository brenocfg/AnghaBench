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
typedef  int /*<<< orphan*/  NextValueExpr ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seqid ; 
 int /*<<< orphan*/  typeId ; 

__attribute__((used)) static bool
_equalNextValueExpr(const NextValueExpr *a, const NextValueExpr *b)
{
	COMPARE_SCALAR_FIELD(seqid);
	COMPARE_SCALAR_FIELD(typeId);

	return true;
}