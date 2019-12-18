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
typedef  int /*<<< orphan*/  uint8_t ;
struct adau1373 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ ADAU1373_DRC (unsigned int) ; 
 unsigned int ADAU1373_DRC_SIZE ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adau1373_load_drc_settings(struct adau1373 *adau1373,
	unsigned int nr, uint8_t *drc)
{
	unsigned int i;

	for (i = 0; i < ADAU1373_DRC_SIZE; ++i)
		regmap_write(adau1373->regmap, ADAU1373_DRC(nr) + i, drc[i]);
}