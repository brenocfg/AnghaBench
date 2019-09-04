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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  field_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x2_sign_extend_optional (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s8
mt76x2_rate_power_val(u8 val)
{
	if (!field_valid(val))
		return 0;

	return mt76x2_sign_extend_optional(val, 7);
}