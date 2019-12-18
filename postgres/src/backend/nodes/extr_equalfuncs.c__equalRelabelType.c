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
typedef  int /*<<< orphan*/  RelabelType ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_COERCIONFORM_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  relabelformat ; 
 int /*<<< orphan*/  resultcollid ; 
 int /*<<< orphan*/  resulttype ; 
 int /*<<< orphan*/  resulttypmod ; 

__attribute__((used)) static bool
_equalRelabelType(const RelabelType *a, const RelabelType *b)
{
	COMPARE_NODE_FIELD(arg);
	COMPARE_SCALAR_FIELD(resulttype);
	COMPARE_SCALAR_FIELD(resulttypmod);
	COMPARE_SCALAR_FIELD(resultcollid);
	COMPARE_COERCIONFORM_FIELD(relabelformat);
	COMPARE_LOCATION_FIELD(location);

	return true;
}