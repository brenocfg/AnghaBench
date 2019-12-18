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
struct regmap {int dummy; } ;

/* Variables and functions */
 int NAU8825_GPIO2JD1 ; 
 int NAU8825_JACK_POLARITY ; 
 int /*<<< orphan*/  NAU8825_REG_I2C_DEVICE_ID ; 
 int /*<<< orphan*/  NAU8825_REG_JACK_DET_CTRL ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool nau8825_is_jack_inserted(struct regmap *regmap)
{
	bool active_high, is_high;
	int status, jkdet;

	regmap_read(regmap, NAU8825_REG_JACK_DET_CTRL, &jkdet);
	active_high = jkdet & NAU8825_JACK_POLARITY;
	regmap_read(regmap, NAU8825_REG_I2C_DEVICE_ID, &status);
	is_high = status & NAU8825_GPIO2JD1;
	/* return jack connection status according to jack insertion logic
	 * active high or active low.
	 */
	return active_high == is_high;
}