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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static inline bool wait_mask(u16 port, u8 mask, u8 allof, u8 noneof, int timeout)
{
	bool delayed = true;

	if (timeout == 0) {
		timeout = 3000000;
		delayed = false;
	}

	while (1) {
		u8 bits = inb(port) & mask;
		if ((bits & allof) == allof && ((bits & noneof) == 0))
			break;
		if (delayed)
			mdelay(1);
		if (--timeout == 0)
			return false;
	}

	return true;
}