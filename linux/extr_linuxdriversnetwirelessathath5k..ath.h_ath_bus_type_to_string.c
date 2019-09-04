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
typedef  enum ath_bus_type { ____Placeholder_ath_bus_type } ath_bus_type ;

/* Variables and functions */
 char const** ath_bus_type_strings ; 

__attribute__((used)) static inline const char *ath_bus_type_to_string(enum ath_bus_type bustype)
{
	return ath_bus_type_strings[bustype];
}