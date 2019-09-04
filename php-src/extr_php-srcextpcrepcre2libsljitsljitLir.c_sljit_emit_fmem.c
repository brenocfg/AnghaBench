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
typedef  struct sljit_compiler* sljit_sw ;
typedef  struct sljit_compiler* sljit_s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_ERROR () ; 
 struct sljit_compiler* SLJIT_ERR_UNSUPPORTED ; 
 int /*<<< orphan*/  SLJIT_UNUSED_ARG (struct sljit_compiler*) ; 
 int /*<<< orphan*/  check_sljit_emit_fmem (struct sljit_compiler*,struct sljit_compiler*,struct sljit_compiler*,struct sljit_compiler*,struct sljit_compiler*) ; 

sljit_s32 sljit_emit_fmem(struct sljit_compiler *compiler, sljit_s32 type,
	sljit_s32 freg,
	sljit_s32 mem, sljit_sw memw)
{
	SLJIT_UNUSED_ARG(compiler);
	SLJIT_UNUSED_ARG(type);
	SLJIT_UNUSED_ARG(freg);
	SLJIT_UNUSED_ARG(mem);
	SLJIT_UNUSED_ARG(memw);

	CHECK_ERROR();
	CHECK(check_sljit_emit_fmem(compiler, type, freg, mem, memw));

	return SLJIT_ERR_UNSUPPORTED;
}