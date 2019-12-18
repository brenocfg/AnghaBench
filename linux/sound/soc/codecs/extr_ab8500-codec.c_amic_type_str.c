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
typedef  enum amic_type { ____Placeholder_amic_type } amic_type ;

/* Variables and functions */
#define  AMIC_TYPE_DIFFERENTIAL 129 
#define  AMIC_TYPE_SINGLE_ENDED 128 

__attribute__((used)) static inline const char *amic_type_str(enum amic_type type)
{
	switch (type) {
	case AMIC_TYPE_DIFFERENTIAL:
		return "DIFFERENTIAL";
	case AMIC_TYPE_SINGLE_ENDED:
		return "SINGLE ENDED";
	default:
		return "Unknown";
	}
}