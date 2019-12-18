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
struct sljit_memory_fragment {int scratches; int saveds; int fscratches; int fsaveds; int local_size; int args; int cpool_diff; void* delay_slot; int /*<<< orphan*/ * cpool; int /*<<< orphan*/ * cpool_unique; struct sljit_memory_fragment* abuf; struct sljit_memory_fragment* buf; scalar_t__ used_size; int /*<<< orphan*/ * next; void* allocator_data; int /*<<< orphan*/  error; } ;
struct sljit_compiler {int scratches; int saveds; int fscratches; int fsaveds; int local_size; int args; int cpool_diff; void* delay_slot; int /*<<< orphan*/ * cpool; int /*<<< orphan*/ * cpool_unique; struct sljit_compiler* abuf; struct sljit_compiler* buf; scalar_t__ used_size; int /*<<< orphan*/ * next; void* allocator_data; int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  sljit_uw ;
typedef  int /*<<< orphan*/  sljit_u8 ;
typedef  int /*<<< orphan*/  sljit_u32 ;
typedef  int /*<<< orphan*/  sljit_u16 ;
typedef  int /*<<< orphan*/  sljit_sw ;
typedef  int /*<<< orphan*/  sljit_s8 ;
typedef  int /*<<< orphan*/  sljit_s32 ;
typedef  int /*<<< orphan*/  sljit_s16 ;
typedef  int /*<<< orphan*/  sljit_p ;

/* Variables and functions */
 int ABUF_SIZE ; 
 int BUF_SIZE ; 
 int CPOOL_SIZE ; 
 int /*<<< orphan*/  SLJIT_COMPILE_ASSERT (int,int /*<<< orphan*/ ) ; 
 int SLJIT_EQUAL ; 
 int SLJIT_EQUAL_F64 ; 
 scalar_t__ SLJIT_F32_OP ; 
 int /*<<< orphan*/  SLJIT_FREE (struct sljit_memory_fragment*,void*) ; 
 scalar_t__ SLJIT_I32_OP ; 
 int SLJIT_JUMP ; 
 int SLJIT_LESS ; 
 scalar_t__ SLJIT_MALLOC (int,void*) ; 
 scalar_t__ SLJIT_REWRITABLE_JUMP ; 
 int /*<<< orphan*/  SLJIT_SUCCESS ; 
 int /*<<< orphan*/  SLJIT_ZEROMEM (struct sljit_memory_fragment*,int) ; 
 void* UNMOVABLE_INS ; 
 int compiler_initialized ; 
 int /*<<< orphan*/  conditional_flags_must_be_even_numbers ; 
 int /*<<< orphan*/  init_compiler () ; 
 int /*<<< orphan*/  int_op_and_single_op_must_be_the_same ; 
 int /*<<< orphan*/  invalid_integer_types ; 
 int /*<<< orphan*/  rewritable_jump_and_single_op_must_not_be_the_same ; 

struct sljit_compiler* sljit_create_compiler(void *allocator_data)
{
	struct sljit_compiler *compiler = (struct sljit_compiler*)SLJIT_MALLOC(sizeof(struct sljit_compiler), allocator_data);
	if (!compiler)
		return NULL;
	SLJIT_ZEROMEM(compiler, sizeof(struct sljit_compiler));

	SLJIT_COMPILE_ASSERT(
		sizeof(sljit_s8) == 1 && sizeof(sljit_u8) == 1
		&& sizeof(sljit_s16) == 2 && sizeof(sljit_u16) == 2
		&& sizeof(sljit_s32) == 4 && sizeof(sljit_u32) == 4
		&& (sizeof(sljit_p) == 4 || sizeof(sljit_p) == 8)
		&& sizeof(sljit_p) <= sizeof(sljit_sw)
		&& (sizeof(sljit_sw) == 4 || sizeof(sljit_sw) == 8)
		&& (sizeof(sljit_uw) == 4 || sizeof(sljit_uw) == 8),
		invalid_integer_types);
	SLJIT_COMPILE_ASSERT(SLJIT_I32_OP == SLJIT_F32_OP,
		int_op_and_single_op_must_be_the_same);
	SLJIT_COMPILE_ASSERT(SLJIT_REWRITABLE_JUMP != SLJIT_F32_OP,
		rewritable_jump_and_single_op_must_not_be_the_same);
	SLJIT_COMPILE_ASSERT(!(SLJIT_EQUAL & 0x1) && !(SLJIT_LESS & 0x1) && !(SLJIT_EQUAL_F64 & 0x1) && !(SLJIT_JUMP & 0x1),
		conditional_flags_must_be_even_numbers);

	/* Only the non-zero members must be set. */
	compiler->error = SLJIT_SUCCESS;

	compiler->allocator_data = allocator_data;
	compiler->buf = (struct sljit_memory_fragment*)SLJIT_MALLOC(BUF_SIZE, allocator_data);
	compiler->abuf = (struct sljit_memory_fragment*)SLJIT_MALLOC(ABUF_SIZE, allocator_data);

	if (!compiler->buf || !compiler->abuf) {
		if (compiler->buf)
			SLJIT_FREE(compiler->buf, allocator_data);
		if (compiler->abuf)
			SLJIT_FREE(compiler->abuf, allocator_data);
		SLJIT_FREE(compiler, allocator_data);
		return NULL;
	}

	compiler->buf->next = NULL;
	compiler->buf->used_size = 0;
	compiler->abuf->next = NULL;
	compiler->abuf->used_size = 0;

	compiler->scratches = -1;
	compiler->saveds = -1;
	compiler->fscratches = -1;
	compiler->fsaveds = -1;
	compiler->local_size = -1;

#if (defined SLJIT_CONFIG_X86_32 && SLJIT_CONFIG_X86_32)
	compiler->args = -1;
#endif

#if (defined SLJIT_CONFIG_ARM_V5 && SLJIT_CONFIG_ARM_V5)
	compiler->cpool = (sljit_uw*)SLJIT_MALLOC(CPOOL_SIZE * sizeof(sljit_uw)
		+ CPOOL_SIZE * sizeof(sljit_u8), allocator_data);
	if (!compiler->cpool) {
		SLJIT_FREE(compiler->buf, allocator_data);
		SLJIT_FREE(compiler->abuf, allocator_data);
		SLJIT_FREE(compiler, allocator_data);
		return NULL;
	}
	compiler->cpool_unique = (sljit_u8*)(compiler->cpool + CPOOL_SIZE);
	compiler->cpool_diff = 0xffffffff;
#endif

#if (defined SLJIT_CONFIG_MIPS && SLJIT_CONFIG_MIPS)
	compiler->delay_slot = UNMOVABLE_INS;
#endif

#if (defined SLJIT_CONFIG_SPARC_32 && SLJIT_CONFIG_SPARC_32)
	compiler->delay_slot = UNMOVABLE_INS;
#endif

#if (defined SLJIT_NEEDS_COMPILER_INIT && SLJIT_NEEDS_COMPILER_INIT)
	if (!compiler_initialized) {
		init_compiler();
		compiler_initialized = 1;
	}
#endif

	return compiler;
}