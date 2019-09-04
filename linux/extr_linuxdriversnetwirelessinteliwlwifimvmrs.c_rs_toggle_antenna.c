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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rs_rate {int ant; } ;

/* Variables and functions */
 int ANT_C ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 size_t* ant_toggle_lookup ; 
 int /*<<< orphan*/  rs_is_valid_ant (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int rs_toggle_antenna(u32 valid_ant, struct rs_rate *rate)
{
	u8 new_ant_type;

	if (!rate->ant || WARN_ON_ONCE(rate->ant & ANT_C))
		return 0;

	if (!rs_is_valid_ant(valid_ant, rate->ant))
		return 0;

	new_ant_type = ant_toggle_lookup[rate->ant];

	while ((new_ant_type != rate->ant) &&
	       !rs_is_valid_ant(valid_ant, new_ant_type))
		new_ant_type = ant_toggle_lookup[new_ant_type];

	if (new_ant_type == rate->ant)
		return 0;

	rate->ant = new_ant_type;

	return 1;
}