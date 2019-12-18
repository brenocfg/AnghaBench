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
typedef  size_t u32 ;
struct snd_bebob {TYPE_2__* spec; } ;
struct TYPE_4__ {TYPE_1__* clock; } ;
struct TYPE_3__ {scalar_t__ types; } ;

/* Variables and functions */
 int EIO ; 
 size_t SAFFIREPRO_CLOCK_SOURCE_COUNT ; 
 size_t SAFFIREPRO_CLOCK_SOURCE_SELECT_MASK ; 
 int /*<<< orphan*/  SAFFIREPRO_OFFSET_CLOCK_SOURCE ; 
 int saffire_read_quad (struct snd_bebob*,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ saffirepro_10_clk_src_types ; 
 char** saffirepro_clk_maps ; 

__attribute__((used)) static int
saffirepro_both_clk_src_get(struct snd_bebob *bebob, unsigned int *id)
{
	int err;
	u32 value;       /* clock source read from hw register */
	const signed char *map;

	err = saffire_read_quad(bebob, SAFFIREPRO_OFFSET_CLOCK_SOURCE, &value);
	if (err < 0)
		goto end;

	/* depending on hardware, use a different mapping */
	if (bebob->spec->clock->types == saffirepro_10_clk_src_types)
		map = saffirepro_clk_maps[0];
	else
		map = saffirepro_clk_maps[1];

	/* In a case that this driver cannot handle the value of register. */
	value &= SAFFIREPRO_CLOCK_SOURCE_SELECT_MASK;
	if (value >= SAFFIREPRO_CLOCK_SOURCE_COUNT || map[value] < 0) {
		err = -EIO;
		goto end;
	}

	*id = (unsigned int)map[value];
end:
	return err;
}