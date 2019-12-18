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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct _ioeventfd {scalar_t__ addr; int length; scalar_t__ datamatch; scalar_t__ wildcard; } ;
typedef  scalar_t__ gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int) ; 

__attribute__((used)) static bool
ioeventfd_in_range(struct _ioeventfd *p, gpa_t addr, int len, const void *val)
{
	u64 _val;

	if (addr != p->addr)
		/* address must be precise for a hit */
		return false;

	if (!p->length)
		/* length = 0 means only look at the address, so always a hit */
		return true;

	if (len != p->length)
		/* address-range must be precise for a hit */
		return false;

	if (p->wildcard)
		/* all else equal, wildcard is always a hit */
		return true;

	/* otherwise, we have to actually compare the data */

	BUG_ON(!IS_ALIGNED((unsigned long)val, len));

	switch (len) {
	case 1:
		_val = *(u8 *)val;
		break;
	case 2:
		_val = *(u16 *)val;
		break;
	case 4:
		_val = *(u32 *)val;
		break;
	case 8:
		_val = *(u64 *)val;
		break;
	default:
		return false;
	}

	return _val == p->datamatch ? true : false;
}