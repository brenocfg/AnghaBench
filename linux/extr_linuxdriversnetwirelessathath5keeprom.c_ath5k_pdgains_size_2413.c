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
struct ath5k_eeprom_info {int* ee_pd_gains; unsigned int* ee_n_piers; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int
ath5k_pdgains_size_2413(struct ath5k_eeprom_info *ee, unsigned int mode)
{
	static const unsigned int pdgains_size[] = { 4, 6, 9, 12 };
	unsigned int sz;

	sz = pdgains_size[ee->ee_pd_gains[mode] - 1];
	sz *= ee->ee_n_piers[mode];

	return sz;
}