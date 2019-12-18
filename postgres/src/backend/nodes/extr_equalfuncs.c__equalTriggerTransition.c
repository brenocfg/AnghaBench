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
typedef  int /*<<< orphan*/  TriggerTransition ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isNew ; 
 int /*<<< orphan*/  isTable ; 
 int /*<<< orphan*/  name ; 

__attribute__((used)) static bool
_equalTriggerTransition(const TriggerTransition *a, const TriggerTransition *b)
{
	COMPARE_STRING_FIELD(name);
	COMPARE_SCALAR_FIELD(isNew);
	COMPARE_SCALAR_FIELD(isTable);

	return true;
}