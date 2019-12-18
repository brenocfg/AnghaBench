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
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  NameGetDatum (int /*<<< orphan*/ *) ; 
 scalar_t__ palloc0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Datum
leftmostvalue_name(void)
{
	NameData   *result = (NameData *) palloc0(NAMEDATALEN);

	return NameGetDatum(result);
}