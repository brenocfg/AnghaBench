#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  warn_unsupported; } ;
struct TYPE_10__ {int /*<<< orphan*/  tok; } ;
struct TYPE_9__ {TYPE_1__* cstr; } ;
struct TYPE_8__ {long long aligned; int packed; int weak; int func_export; int func_import; int /*<<< orphan*/  mode; int /*<<< orphan*/  func_call; int /*<<< orphan*/  alias_target; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; scalar_t__ data; } ;
typedef  TYPE_2__ AttributeDef ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC_CDECL ; 
 int /*<<< orphan*/  FUNC_FASTCALL1 ; 
 int /*<<< orphan*/  FUNC_FASTCALLW ; 
 int /*<<< orphan*/  FUNC_STDCALL ; 
 long long MAX_ALIGN ; 
 int /*<<< orphan*/  TCC_ERR (char*) ; 
#define  TOK_ALIAS1 156 
#define  TOK_ALIAS2 155 
#define  TOK_ALIGNED1 154 
#define  TOK_ALIGNED2 153 
 char TOK_ATTRIBUTE1 ; 
 char TOK_ATTRIBUTE2 ; 
#define  TOK_CDECL1 152 
#define  TOK_CDECL2 151 
#define  TOK_CDECL3 150 
#define  TOK_DLLEXPORT 149 
#define  TOK_DLLIMPORT 148 
#define  TOK_FASTCALL1 147 
#define  TOK_FASTCALL2 146 
#define  TOK_FASTCALL3 145 
 char TOK_IDENT ; 
#define  TOK_MODE 144 
#define  TOK_MODE_DI 143 
#define  TOK_MODE_HI 142 
#define  TOK_MODE_SI 141 
#define  TOK_NORETURN1 140 
#define  TOK_NORETURN2 139 
#define  TOK_PACKED1 138 
#define  TOK_PACKED2 137 
#define  TOK_REGPARM1 136 
#define  TOK_REGPARM2 135 
#define  TOK_STDCALL1 134 
#define  TOK_STDCALL2 133 
#define  TOK_STDCALL3 132 
 char TOK_STR ; 
#define  TOK_UNUSED1 131 
#define  TOK_UNUSED2 130 
#define  TOK_WEAK1 129 
#define  TOK_WEAK2 128 
 int /*<<< orphan*/  VT_INT16 ; 
 int /*<<< orphan*/  VT_INT32 ; 
 int /*<<< orphan*/  VT_INT64 ; 
 int /*<<< orphan*/  expect (char*) ; 
 long long expr_const () ; 
 int /*<<< orphan*/  get_tok_str (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next () ; 
 int /*<<< orphan*/  skip (char) ; 
 TYPE_5__* tcc_state ; 
 int /*<<< orphan*/  tcc_warning (char*,int /*<<< orphan*/ ) ; 
 char tok ; 
 TYPE_4__* tok_alloc (char*,int /*<<< orphan*/ ) ; 
 TYPE_3__ tokc ; 

__attribute__((used)) static void parse_attribute(AttributeDef *ad) {
	int t;
	long long n;

	while (tok == TOK_ATTRIBUTE1 || tok == TOK_ATTRIBUTE2) {
		next ();
		skip ('(');
		skip ('(');
		while (tok != ')') {
			if (tok < TOK_IDENT) {
				expect ("attribute name");
			}
			t = tok;
			next ();
			switch (t) {
			case TOK_ALIAS1:
			case TOK_ALIAS2:
				skip ('(');
				if (tok != TOK_STR) {
					expect ("alias(\"target\")");
				}
				ad->alias_target =	/* save string as token, for later */
						   tok_alloc ((char *) tokc.cstr->data, tokc.cstr->size - 1)->tok;
				next ();
				skip (')');
				break;
			case TOK_ALIGNED1:
			case TOK_ALIGNED2:
				if (tok == '(') {
					next ();
					n = expr_const ();
					if (n <= 0 || (n & (n - 1)) != 0) {
						TCC_ERR ("alignment must be a positive power of two");
					}
					skip (')');
				} else {
					n = MAX_ALIGN;
				}
				ad->aligned = n;
				break;
			case TOK_PACKED1:
			case TOK_PACKED2:
				ad->packed = 1;
				break;
			case TOK_WEAK1:
			case TOK_WEAK2:
				ad->weak = 1;
				break;
			case TOK_UNUSED1:
			case TOK_UNUSED2:
				/* currently, no need to handle it because tcc does not
				   track unused objects */
				break;
			case TOK_NORETURN1:
			case TOK_NORETURN2:
				/* currently, no need to handle it because tcc does not
				   track unused objects */
				break;
			case TOK_CDECL1:
			case TOK_CDECL2:
			case TOK_CDECL3:
				ad->func_call = FUNC_CDECL;
				break;
			case TOK_STDCALL1:
			case TOK_STDCALL2:
			case TOK_STDCALL3:
				ad->func_call = FUNC_STDCALL;
				break;
#ifdef TCC_TARGET_I386
			case TOK_REGPARM1:
			case TOK_REGPARM2:
				skip ('(');
				n = expr_const ();
				if (n > 3) {
					n = 3;
				} else if (n < 0) {
					n = 0;
				}
				if (n > 0) {
					ad->func_call = FUNC_FASTCALL1 + n - 1;
				}
				skip (')');
				break;
			case TOK_FASTCALL1:
			case TOK_FASTCALL2:
			case TOK_FASTCALL3:
				ad->func_call = FUNC_FASTCALLW;
				break;
#endif
			case TOK_MODE:
				skip ('(');
				switch (tok) {
				case TOK_MODE_DI:
					ad->mode = VT_INT64 + 1;
					break;
				case TOK_MODE_HI:
					ad->mode = VT_INT16 + 1;
					break;
				case TOK_MODE_SI:
					ad->mode = VT_INT32 + 1;
					break;
				default:
					tcc_warning ("__mode__(%s) not supported\n", get_tok_str (tok, NULL));
					break;
				}
				next ();
				skip (')');
				break;
			case TOK_DLLEXPORT:
				ad->func_export = 1;
				break;
			case TOK_DLLIMPORT:
				ad->func_import = 1;
				break;
			default:
				if (tcc_state->warn_unsupported) {
					tcc_warning ("'%s' attribute ignored", get_tok_str (t, NULL));
				}
				/* skip parameters */
				if (tok == '(') {
					int parenthesis = 0;
					do {
						if (tok == '(') {
							parenthesis++;
						} else if (tok == ')') {
							parenthesis--;
						}
						next ();
					} while (parenthesis && tok != -1);
				}
				break;
			}
			if (tok != ',') {
				break;
			}
			next ();
		}
		skip (')');
		skip (')');
	}
}