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
typedef  scalar_t__ u64 ;

/* Variables and functions */
#define  CMDF_ROUND_DOWN 130 
 unsigned int CMDF_ROUND_MASK ; 
#define  CMDF_ROUND_NEAREST 129 
#define  CMDF_ROUND_UP 128 
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  DIV_ROUND_UP (unsigned int,unsigned int) ; 
 scalar_t__ UINT_MAX ; 
 unsigned int do_div (scalar_t__,unsigned int) ; 

__attribute__((used)) static unsigned int pci230_divide_ns(u64 ns, unsigned int timebase,
				     unsigned int flags)
{
	u64 div;
	unsigned int rem;

	div = ns;
	rem = do_div(div, timebase);
	switch (flags & CMDF_ROUND_MASK) {
	default:
	case CMDF_ROUND_NEAREST:
		div += DIV_ROUND_CLOSEST(rem, timebase);
		break;
	case CMDF_ROUND_DOWN:
		break;
	case CMDF_ROUND_UP:
		div += DIV_ROUND_UP(rem, timebase);
		break;
	}
	return div > UINT_MAX ? UINT_MAX : (unsigned int)div;
}