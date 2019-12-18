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
struct mtpav {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_mtpav_send_byte (struct mtpav*,int) ; 

__attribute__((used)) static void snd_mtpav_portscan(struct mtpav *chip)	// put mtp into smart routing mode
{
	u8 p;

	for (p = 0; p < 8; p++) {
		snd_mtpav_send_byte(chip, 0xf5);
		snd_mtpav_send_byte(chip, p);
		snd_mtpav_send_byte(chip, 0xfe);
	}
}