#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ channel; } ;
struct TYPE_3__ {scalar_t__ channel_at_start; } ;
struct b43legacy_wldev {TYPE_2__ phy; TYPE_1__ noisecalc; } ;

/* Variables and functions */
 int B43legacy_MACCMD_BGNOISE ; 
 int /*<<< orphan*/  B43legacy_MMIO_MACCMD ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  b43legacy_jssi_write (struct b43legacy_wldev*,int) ; 
 int b43legacy_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43legacy_generate_noise_sample(struct b43legacy_wldev *dev)
{
	b43legacy_jssi_write(dev, 0x7F7F7F7F);
	b43legacy_write32(dev, B43legacy_MMIO_MACCMD,
			  b43legacy_read32(dev, B43legacy_MMIO_MACCMD)
			  | B43legacy_MACCMD_BGNOISE);
	B43legacy_WARN_ON(dev->noisecalc.channel_at_start !=
			    dev->phy.channel);
}