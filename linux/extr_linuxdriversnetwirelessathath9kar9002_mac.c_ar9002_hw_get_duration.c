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
struct ath_hw {int dummy; } ;
struct ar5416_desc {int /*<<< orphan*/  ds_ctl5; int /*<<< orphan*/  ds_ctl4; } ;

/* Variables and functions */
 struct ar5416_desc* AR5416DESC (void const*) ; 
 int /*<<< orphan*/  AR_PacketDur0 ; 
 int /*<<< orphan*/  AR_PacketDur1 ; 
 int /*<<< orphan*/  AR_PacketDur2 ; 
 int /*<<< orphan*/  AR_PacketDur3 ; 
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ar9002_hw_get_duration(struct ath_hw *ah, const void *ds, int index)
{
	struct ar5416_desc *ads = AR5416DESC(ds);

	switch (index) {
	case 0:
		return MS(READ_ONCE(ads->ds_ctl4), AR_PacketDur0);
	case 1:
		return MS(READ_ONCE(ads->ds_ctl4), AR_PacketDur1);
	case 2:
		return MS(READ_ONCE(ads->ds_ctl5), AR_PacketDur2);
	case 3:
		return MS(READ_ONCE(ads->ds_ctl5), AR_PacketDur3);
	default:
		return -1;
	}
}