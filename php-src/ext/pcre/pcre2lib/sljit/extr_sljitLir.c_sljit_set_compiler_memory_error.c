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
struct sljit_compiler {scalar_t__ error; } ;

/* Variables and functions */
 scalar_t__ SLJIT_ERR_ALLOC_FAILED ; 
 scalar_t__ SLJIT_SUCCESS ; 

void sljit_set_compiler_memory_error(struct sljit_compiler *compiler)
{
	if (compiler->error == SLJIT_SUCCESS)
		compiler->error = SLJIT_ERR_ALLOC_FAILED;
}