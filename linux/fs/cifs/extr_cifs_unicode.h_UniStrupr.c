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
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  UniToupper (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (scalar_t__) ; 

__attribute__((used)) static inline __le16 *
UniStrupr(register __le16 *upin)
{
	register __le16 *up;

	up = upin;
	while (*up) {		/* For all characters */
		*up = cpu_to_le16(UniToupper(le16_to_cpu(*up)));
		up++;
	}
	return upin;		/* Return input pointer */
}