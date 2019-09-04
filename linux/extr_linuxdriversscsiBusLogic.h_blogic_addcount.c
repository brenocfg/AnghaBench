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
struct blogic_byte_count {unsigned int units; int /*<<< orphan*/  billions; } ;

/* Variables and functions */

__attribute__((used)) static inline void blogic_addcount(struct blogic_byte_count *bytecount,
					unsigned int amount)
{
	bytecount->units += amount;
	if (bytecount->units > 999999999) {
		bytecount->units -= 1000000000;
		bytecount->billions++;
	}
}