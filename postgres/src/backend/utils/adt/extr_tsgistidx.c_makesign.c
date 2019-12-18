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
typedef  size_t int32 ;
typedef  int /*<<< orphan*/  SignTSVector ;
typedef  scalar_t__ BITVECP ;
typedef  int /*<<< orphan*/  BITVEC ;

/* Variables and functions */
 size_t ARRNELEM (int /*<<< orphan*/ *) ; 
 size_t* GETARR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HASH (scalar_t__,size_t) ; 
 int /*<<< orphan*/  MemSet (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
makesign(BITVECP sign, SignTSVector *a)
{
	int32		k,
				len = ARRNELEM(a);
	int32	   *ptr = GETARR(a);

	MemSet((void *) sign, 0, sizeof(BITVEC));
	for (k = 0; k < len; k++)
		HASH(sign, ptr[k]);
}