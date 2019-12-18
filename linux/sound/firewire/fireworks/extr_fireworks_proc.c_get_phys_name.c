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
struct snd_efw_phys_grp {size_t type; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const* const*) ; 

__attribute__((used)) static inline const char*
get_phys_name(struct snd_efw_phys_grp *grp, bool input)
{
	static const char *const ch_type[] = {
		"Analog", "S/PDIF", "ADAT", "S/PDIF or ADAT", "Mirroring",
		"Headphones", "I2S", "Guitar", "Pirzo Guitar", "Guitar String",
	};

	if (grp->type < ARRAY_SIZE(ch_type))
		return ch_type[grp->type];
	else if (input)
		return "Input";
	else
		return "Output";
}