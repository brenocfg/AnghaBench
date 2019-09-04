#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_CCK_RATE_11MB ; 
 int /*<<< orphan*/  B43_CCK_RATE_1MB ; 
 int /*<<< orphan*/  B43_CCK_RATE_2MB ; 
 int /*<<< orphan*/  B43_CCK_RATE_5MB ; 
 int /*<<< orphan*/  B43_OFDM_RATE_12MB ; 
 int /*<<< orphan*/  B43_OFDM_RATE_18MB ; 
 int /*<<< orphan*/  B43_OFDM_RATE_24MB ; 
 int /*<<< orphan*/  B43_OFDM_RATE_36MB ; 
 int /*<<< orphan*/  B43_OFDM_RATE_48MB ; 
 int /*<<< orphan*/  B43_OFDM_RATE_54MB ; 
 int /*<<< orphan*/  B43_OFDM_RATE_6MB ; 
 int /*<<< orphan*/  B43_OFDM_RATE_9MB ; 
#define  B43_PHYTYPE_B 133 
#define  B43_PHYTYPE_G 132 
#define  B43_PHYTYPE_HT 131 
#define  B43_PHYTYPE_LCN 130 
#define  B43_PHYTYPE_LP 129 
#define  B43_PHYTYPE_N 128 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_rate_memory_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_rate_memory_init(struct b43_wldev *dev)
{
	switch (dev->phy.type) {
	case B43_PHYTYPE_G:
	case B43_PHYTYPE_N:
	case B43_PHYTYPE_LP:
	case B43_PHYTYPE_HT:
	case B43_PHYTYPE_LCN:
		b43_rate_memory_write(dev, B43_OFDM_RATE_6MB, 1);
		b43_rate_memory_write(dev, B43_OFDM_RATE_9MB, 1);
		b43_rate_memory_write(dev, B43_OFDM_RATE_12MB, 1);
		b43_rate_memory_write(dev, B43_OFDM_RATE_18MB, 1);
		b43_rate_memory_write(dev, B43_OFDM_RATE_24MB, 1);
		b43_rate_memory_write(dev, B43_OFDM_RATE_36MB, 1);
		b43_rate_memory_write(dev, B43_OFDM_RATE_48MB, 1);
		b43_rate_memory_write(dev, B43_OFDM_RATE_54MB, 1);
		/* fallthrough */
	case B43_PHYTYPE_B:
		b43_rate_memory_write(dev, B43_CCK_RATE_1MB, 0);
		b43_rate_memory_write(dev, B43_CCK_RATE_2MB, 0);
		b43_rate_memory_write(dev, B43_CCK_RATE_5MB, 0);
		b43_rate_memory_write(dev, B43_CCK_RATE_11MB, 0);
		break;
	default:
		B43_WARN_ON(1);
	}
}