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
typedef  int /*<<< orphan*/  SQLValueFunction ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  op ; 
 int /*<<< orphan*/  type ; 
 int /*<<< orphan*/  typmod ; 

__attribute__((used)) static bool
_equalSQLValueFunction(const SQLValueFunction *a, const SQLValueFunction *b)
{
	COMPARE_SCALAR_FIELD(op);
	COMPARE_SCALAR_FIELD(type);
	COMPARE_SCALAR_FIELD(typmod);
	COMPARE_LOCATION_FIELD(location);

	return true;
}