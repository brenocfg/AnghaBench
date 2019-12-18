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
typedef  int /*<<< orphan*/  decimal ;

/* Variables and functions */
 int ECPG_INFORMIX_NUM_OVERFLOW ; 
 int ECPG_INFORMIX_NUM_UNDERFLOW ; 
#define  PGTYPES_NUM_OVERFLOW 128 
 int /*<<< orphan*/  PGTYPESnumeric_mul ; 
 int deccall3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int errno ; 

int
decmul(decimal *n1, decimal *n2, decimal *result)
{
	int			i;

	errno = 0;
	i = deccall3(n1, n2, result, PGTYPESnumeric_mul);

	if (i != 0)
		switch (errno)
		{
			case PGTYPES_NUM_OVERFLOW:
				return ECPG_INFORMIX_NUM_OVERFLOW;
				break;
			default:
				return ECPG_INFORMIX_NUM_UNDERFLOW;
				break;
		}

	return 0;
}