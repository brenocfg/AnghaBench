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
typedef  int u64 ;
struct tnum {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TNUM (int /*<<< orphan*/ ,int) ; 
 struct tnum tnum_add (struct tnum,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tnum hma(struct tnum acc, u64 value, u64 mask)
{
	while (mask) {
		if (mask & 1)
			acc = tnum_add(acc, TNUM(0, value));
		mask >>= 1;
		value <<= 1;
	}
	return acc;
}