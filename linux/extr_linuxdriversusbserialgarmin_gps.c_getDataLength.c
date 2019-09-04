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
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int __le32_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int getDataLength(const __u8 *usbPacket)
{
	return __le32_to_cpup((__le32 *)(usbPacket+8));
}