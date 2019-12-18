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
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
#define  BMS_EMPTY_SET 130 
#define  BMS_MULTIPLE 129 
#define  BMS_SINGLETON 128 
 int bms_is_member (int,int /*<<< orphan*/  const*) ; 
 int bms_membership (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool
bms_is_subset_singleton(const Bitmapset *s, int x)
{
	switch (bms_membership(s))
	{
		case BMS_EMPTY_SET:
			return true;
		case BMS_SINGLETON:
			return bms_is_member(x, s);
		case BMS_MULTIPLE:
			return false;
	}
	/* can't get here... */
	return false;
}