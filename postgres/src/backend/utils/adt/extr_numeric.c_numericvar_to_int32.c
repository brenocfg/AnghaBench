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
typedef  scalar_t__ int64 ;
typedef  scalar_t__ int32 ;
typedef  int /*<<< orphan*/  NumericVar ;

/* Variables and functions */
 int /*<<< orphan*/  numericvar_to_int64 (int /*<<< orphan*/  const*,scalar_t__*) ; 

__attribute__((used)) static bool
numericvar_to_int32(const NumericVar *var, int32 *result)
{
	int64		val;

	if (!numericvar_to_int64(var, &val))
		return false;

	/* Down-convert to int4 */
	*result = (int32) val;

	/* Test for overflow by reverse-conversion. */
	return ((int64) *result == val);
}