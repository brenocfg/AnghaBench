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
typedef  int /*<<< orphan*/  m_pool_p ;

/* Variables and functions */
 int DEBUG_ALLOC ; 
 int DEBUG_FLAGS ; 
 int /*<<< orphan*/  ___sym_mfree (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,void*) ; 

__attribute__((used)) static void __sym_mfree(m_pool_p mp, void *ptr, int size, char *name)
{
	if (DEBUG_FLAGS & DEBUG_ALLOC)
		printf ("freeing %-10s[%4d] @%p.\n", name, size, ptr);

	___sym_mfree(mp, ptr, size);
}