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
typedef  int /*<<< orphan*/  trgm ;
typedef  scalar_t__ int32 ;
typedef  int /*<<< orphan*/  TRGM ;
typedef  scalar_t__ BITVECP ;
typedef  int /*<<< orphan*/  BITVEC ;

/* Variables and functions */
 scalar_t__ ARRNELEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPTRGM (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GETARR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HASH (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MemSet (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SETBIT (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGLENBIT ; 

__attribute__((used)) static void
makesign(BITVECP sign, TRGM *a)
{
	int32		k,
				len = ARRNELEM(a);
	trgm	   *ptr = GETARR(a);
	int32		tmp = 0;

	MemSet((void *) sign, 0, sizeof(BITVEC));
	SETBIT(sign, SIGLENBIT);	/* set last unused bit */
	for (k = 0; k < len; k++)
	{
		CPTRGM(((char *) &tmp), ptr + k);
		HASH(sign, tmp);
	}
}