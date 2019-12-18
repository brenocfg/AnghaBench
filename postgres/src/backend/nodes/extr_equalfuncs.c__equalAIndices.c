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
typedef  int /*<<< orphan*/  A_Indices ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_slice ; 
 int /*<<< orphan*/  lidx ; 
 int /*<<< orphan*/  uidx ; 

__attribute__((used)) static bool
_equalAIndices(const A_Indices *a, const A_Indices *b)
{
	COMPARE_SCALAR_FIELD(is_slice);
	COMPARE_NODE_FIELD(lidx);
	COMPARE_NODE_FIELD(uidx);

	return true;
}