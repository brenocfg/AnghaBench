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
typedef  int u16 ;

/* Variables and functions */
 scalar_t__ bdaddr_type_is_le (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_valid_psm(u16 psm, u8 dst_type) {
	if (!psm)
		return false;

	if (bdaddr_type_is_le(dst_type))
		return (psm <= 0x00ff);

	/* PSM must be odd and lsb of upper byte must be 0 */
	return ((psm & 0x0101) == 0x0001);
}