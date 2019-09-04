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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ds1307 {int /*<<< orphan*/  dev; } ;
struct chip_desc {int /*<<< orphan*/  (* do_trickle_setup ) (struct ds1307*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 scalar_t__ device_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ device_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ds1307*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 ds1307_trickle_init(struct ds1307 *ds1307,
			      const struct chip_desc *chip)
{
	u32 ohms;
	bool diode = true;

	if (!chip->do_trickle_setup)
		return 0;

	if (device_property_read_u32(ds1307->dev, "trickle-resistor-ohms",
				     &ohms))
		return 0;

	if (device_property_read_bool(ds1307->dev, "trickle-diode-disable"))
		diode = false;

	return chip->do_trickle_setup(ds1307, ohms, diode);
}