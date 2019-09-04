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

/* Variables and functions */
 scalar_t__ isalnum (char const) ; 
 scalar_t__ isspace (char const) ; 

__attribute__((used)) static const char *retrieve_id_from_card_name(const char *name)
{
	const char *spos = name;

	while (*name) {
		if (isspace(*name) && isalnum(name[1]))
			spos = name + 1;
		name++;
	}
	return spos;
}