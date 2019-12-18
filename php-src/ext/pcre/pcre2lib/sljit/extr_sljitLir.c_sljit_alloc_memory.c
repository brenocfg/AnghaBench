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
struct sljit_compiler {int dummy; } ;
typedef  int sljit_s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ERROR_PTR () ; 
 void* ensure_abuf (struct sljit_compiler*,int) ; 

void* sljit_alloc_memory(struct sljit_compiler *compiler, sljit_s32 size)
{
	CHECK_ERROR_PTR();

#if (defined SLJIT_64BIT_ARCHITECTURE && SLJIT_64BIT_ARCHITECTURE)
	if (size <= 0 || size > 128)
		return NULL;
	size = (size + 7) & ~7;
#else
	if (size <= 0 || size > 64)
		return NULL;
	size = (size + 3) & ~3;
#endif
	return ensure_abuf(compiler, size);
}