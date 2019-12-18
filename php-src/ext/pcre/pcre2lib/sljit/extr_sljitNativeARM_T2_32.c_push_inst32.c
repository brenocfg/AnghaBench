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
struct sljit_compiler {int size; } ;
typedef  int sljit_u16 ;
typedef  int /*<<< orphan*/  sljit_s32 ;
typedef  int sljit_ins ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int /*<<< orphan*/  SLJIT_SUCCESS ; 
 scalar_t__ ensure_buf (struct sljit_compiler*,int) ; 

__attribute__((used)) static sljit_s32 push_inst32(struct sljit_compiler *compiler, sljit_ins inst)
{
	sljit_u16 *ptr = (sljit_u16*)ensure_buf(compiler, sizeof(sljit_ins));
	FAIL_IF(!ptr);
	*ptr++ = inst >> 16;
	*ptr = inst;
	compiler->size += 2;
	return SLJIT_SUCCESS;
}