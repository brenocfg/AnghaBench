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
 scalar_t__ EINVAL ; 
#define  EI_ETYPE_ERRNO 130 
#define  EI_ETYPE_ERRNO_NULL 129 
#define  EI_ETYPE_NULL 128 
 scalar_t__ MAX_ERRNO ; 
 int get_injectable_error_type (unsigned long) ; 

__attribute__((used)) static unsigned long adjust_error_retval(unsigned long addr, unsigned long retv)
{
	switch (get_injectable_error_type(addr)) {
	case EI_ETYPE_NULL:
		if (retv != 0)
			return 0;
		break;
	case EI_ETYPE_ERRNO:
		if (retv < (unsigned long)-MAX_ERRNO)
			return (unsigned long)-EINVAL;
		break;
	case EI_ETYPE_ERRNO_NULL:
		if (retv != 0 && retv < (unsigned long)-MAX_ERRNO)
			return (unsigned long)-EINVAL;
		break;
	}

	return retv;
}