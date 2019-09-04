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
struct dasd_eckd_characteristics {int dev_type; } ;

/* Variables and functions */
 int ceil_quot (unsigned int,int) ; 

__attribute__((used)) static unsigned int
recs_per_track(struct dasd_eckd_characteristics * rdc,
	       unsigned int kl, unsigned int dl)
{
	int dn, kn;

	switch (rdc->dev_type) {
	case 0x3380:
		if (kl)
			return 1499 / (15 + 7 + ceil_quot(kl + 12, 32) +
				       ceil_quot(dl + 12, 32));
		else
			return 1499 / (15 + ceil_quot(dl + 12, 32));
	case 0x3390:
		dn = ceil_quot(dl + 6, 232) + 1;
		if (kl) {
			kn = ceil_quot(kl + 6, 232) + 1;
			return 1729 / (10 + 9 + ceil_quot(kl + 6 * kn, 34) +
				       9 + ceil_quot(dl + 6 * dn, 34));
		} else
			return 1729 / (10 + 9 + ceil_quot(dl + 6 * dn, 34));
	case 0x9345:
		dn = ceil_quot(dl + 6, 232) + 1;
		if (kl) {
			kn = ceil_quot(kl + 6, 232) + 1;
			return 1420 / (18 + 7 + ceil_quot(kl + 6 * kn, 34) +
				       ceil_quot(dl + 6 * dn, 34));
		} else
			return 1420 / (18 + 7 + ceil_quot(dl + 6 * dn, 34));
	}
	return 0;
}