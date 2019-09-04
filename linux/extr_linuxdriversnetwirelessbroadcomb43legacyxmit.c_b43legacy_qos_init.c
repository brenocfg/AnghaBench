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
struct b43legacy_wldev {int dummy; } ;

/* Variables and functions */
 int B43legacy_HF_EDCF ; 
 int b43legacy_hf_read (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_hf_write (struct b43legacy_wldev*,int) ; 
 int b43legacy_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int,int) ; 

void b43legacy_qos_init(struct b43legacy_wldev *dev)
{
	/* FIXME: This function must probably be called from the mac80211
	 * config callback. */
return;

	b43legacy_hf_write(dev, b43legacy_hf_read(dev) | B43legacy_HF_EDCF);
	/* FIXME kill magic */
	b43legacy_write16(dev, 0x688,
			  b43legacy_read16(dev, 0x688) | 0x4);


	/*TODO: We might need some stack support here to get the values. */
}