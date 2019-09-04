#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
struct TYPE_24__ {void* t; } ;
struct TYPE_23__ {void* t; } ;
struct TYPE_22__ {void* t; } ;
struct TYPE_21__ {void* t; } ;
struct TYPE_20__ {void* t; } ;
struct TYPE_19__ {int bits; } ;
struct TYPE_18__ {scalar_t__ nb_errors; int error_set_jmp_enabled; int /*<<< orphan*/  error_jmp_buf; } ;
struct TYPE_17__ {int /*<<< orphan*/ * buf_ptr; } ;
struct TYPE_16__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  t; } ;
struct TYPE_15__ {int /*<<< orphan*/  t; } ;
typedef  TYPE_1__ TCCState ;
typedef  int /*<<< orphan*/  Sym ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC_CDECL ; 
 int /*<<< orphan*/  FUNC_OLD ; 
 int PARSE_FLAG_PREPROCESS ; 
 int PARSE_FLAG_TOK_NUM ; 
 int /*<<< orphan*/  SYM_FIELD ; 
 scalar_t__ TOK_EOF ; 
 int TOK_FLAG_BOF ; 
 int TOK_FLAG_BOL ; 
 int /*<<< orphan*/  VT_CONST ; 
 int /*<<< orphan*/  VT_FUNC ; 
 int /*<<< orphan*/  VT_INT16 ; 
 void* VT_INT32 ; 
 void* VT_INT64 ; 
 void* VT_INT8 ; 
 int /*<<< orphan*/  ch ; 
 TYPE_7__ char_pointer_type ; 
 int /*<<< orphan*/  decl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * define_stack ; 
 int /*<<< orphan*/  expect (char*) ; 
 TYPE_13__* file ; 
 int /*<<< orphan*/  free_defines (int /*<<< orphan*/ *) ; 
 TYPE_12__ func_old_type ; 
 char* funcname ; 
 int /*<<< orphan*/  global_stack ; 
 TYPE_11__ int16_type ; 
 TYPE_4__ int32_type ; 
 TYPE_9__ int64_type ; 
 TYPE_8__ int8_type ; 
 int /*<<< orphan*/  local_stack ; 
 int /*<<< orphan*/  mk_pointer (TYPE_7__*) ; 
 int /*<<< orphan*/  next () ; 
 int nocode_wanted ; 
 int parse_flags ; 
 int /*<<< orphan*/  preprocess_init (TYPE_1__*) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 TYPE_5__ size_type ; 
 int /*<<< orphan*/  sym_pop (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sym_push (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* tcc_state ; 
 scalar_t__ tok ; 
 int tok_flags ; 

__attribute__((used)) static int tcc_compile(TCCState *s1)
{
	Sym *define_start;

#ifdef INC_DEBUG
	printf ("%s: **** new file\n", file->filename);
#endif
	preprocess_init (s1);

	funcname = "";

	/* define some often used types */
	int8_type.t = VT_INT8;
	int16_type.t = VT_INT16;
	int32_type.t = VT_INT32;
	int64_type.t = VT_INT64;

	char_pointer_type.t = VT_INT8;
	mk_pointer (&char_pointer_type);

	if (tcc_state->bits != 64) {
		size_type.t = VT_INT32;
	} else {
		size_type.t = VT_INT64;
	}

	func_old_type.t = VT_FUNC;
	func_old_type.ref = sym_push (SYM_FIELD, &int32_type, FUNC_CDECL, FUNC_OLD);

// FIXME: Should depend on the target options too
#ifdef TCC_TARGET_ARM
	arm_init_types ();
#endif

#if 0
	/* define 'void *alloca(unsigned int)' builtin function */
	{
		Sym *s1;

		p = anon_sym++;
		sym = sym_push (p, mk_pointer (VT_VOID), FUNC_CDECL, FUNC_NEW);
		s1 = sym_push (SYM_FIELD, VT_UNSIGNED | VT_INT, 0, 0);
		s1->next = NULL;
		sym->next = s1;
		sym_push (TOK_alloca, VT_FUNC | (p << VT_STRUCT_SHIFT), VT_CONST, 0);
	}
#endif

	define_start = define_stack;
	nocode_wanted = 1;

	if (setjmp (s1->error_jmp_buf) == 0) {
		s1->nb_errors = 0;
		s1->error_set_jmp_enabled = 1;

		ch = file->buf_ptr[0];
		tok_flags = TOK_FLAG_BOL | TOK_FLAG_BOF;
		parse_flags = PARSE_FLAG_PREPROCESS | PARSE_FLAG_TOK_NUM;
		// pvtop = vtop;
		next ();
		decl (VT_CONST);
		if (tok != TOK_EOF) {
			expect ("declaration");
		}
#if 0
		if (pvtop != vtop) {
			fprintf (stderr, "internal compiler error:"
				" vstack leak? (%d)", vtop - pvtop);
		}
#endif
	}

	s1->error_set_jmp_enabled = 0;

	/* reset define stack, but leave -Dsymbols (may be incorrect if
	   they are undefined) */
	free_defines (define_start);

	sym_pop (&global_stack, NULL);
	sym_pop (&local_stack, NULL);

	return s1->nb_errors != 0? -1: 0;
}