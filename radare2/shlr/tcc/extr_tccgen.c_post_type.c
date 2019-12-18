#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kind ;
struct TYPE_20__ {int t; } ;
struct TYPE_19__ {int i; } ;
struct TYPE_24__ {int r; TYPE_2__ type; TYPE_1__ c; } ;
struct TYPE_23__ {int func_args; } ;
struct TYPE_22__ {int t; TYPE_3__* ref; } ;
struct TYPE_21__ {struct TYPE_21__* next; } ;
typedef  TYPE_3__ Sym ;
typedef  TYPE_4__ CType ;
typedef  TYPE_5__ AttributeDef ;

/* Variables and functions */
 int FUNC_ELLIPSIS ; 
 int FUNC_NEW ; 
 int FUNC_OLD ; 
 int /*<<< orphan*/  INT_ATTR (TYPE_5__*) ; 
 int PTR_SIZE ; 
 int /*<<< orphan*/  R_FREE (char*) ; 
 int SYM_FIELD ; 
 int /*<<< orphan*/  TCC_ERR (char*) ; 
 char TOK_DOTS ; 
 char TOK_RESTRICT1 ; 
 int TOK_UIDENT ; 
 int TYPE_ABSTRACT ; 
 int TYPE_DIRECT ; 
 int VT_ARRAY ; 
 int VT_BTYPE ; 
 int VT_CONST ; 
 int VT_CONSTANT ; 
 int VT_FUNC ; 
 int VT_INT32 ; 
 int VT_LVAL ; 
 int VT_PTR ; 
 int VT_SYM ; 
 int VT_VALMASK ; 
 int VT_VLA ; 
 int VT_VOID ; 
 int arraysize ; 
 int /*<<< orphan*/  convert_parameter_type (TYPE_4__*) ; 
 int /*<<< orphan*/  expect (char*) ; 
 int /*<<< orphan*/  expr_const () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gexpr () ; 
 int /*<<< orphan*/  global_symname ; 
 char* global_type ; 
 int /*<<< orphan*/  is_integer_btype (int) ; 
 int /*<<< orphan*/  local_stack ; 
 int /*<<< orphan*/  next () ; 
 scalar_t__ nocode_wanted ; 
 int /*<<< orphan*/  parse_btype (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  skip (char) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 TYPE_3__* sym_push (int,TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcc_appendf (char*,char*,...) ; 
 scalar_t__ tcc_nerr () ; 
 char tok ; 
 int /*<<< orphan*/  type_decl (TYPE_4__*,TYPE_5__*,int*,int) ; 
 int type_size (TYPE_4__*,int*) ; 
 int /*<<< orphan*/  type_to_str (char*,int,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpushll (int /*<<< orphan*/ ) ; 
 TYPE_6__* vtop ; 

__attribute__((used)) static void post_type(CType *type, AttributeDef *ad) {
	int n, l, t1, arg_size, align;
	Sym **plast, *s, *first;
	AttributeDef ad1;
	CType pt;
	char *symname = NULL;
	int narg = 0;

	if (tok == '(') {
		/* function declaration */
		next ();
		l = 0;
		first = NULL;
		plast = &first;
		{
			const char *ret_type = global_type;
			free (symname);
			symname = strdup (global_symname);
			tcc_appendf ("func.%s.ret=%s\n", symname, ret_type);
			tcc_appendf ("func.%s.cc=%s\n", symname, "cdecl");	// TODO
			tcc_appendf ("%s=func\n", symname);
		}
		arg_size = 0;
		if (tok != ')') {
			while (tcc_nerr () == 0) {
				/* read param name and compute offset */
				if (l != FUNC_OLD) {
					if (!parse_btype (&pt, &ad1)) {
						if (l) {
							TCC_ERR ("invalid type");
						} else {
							l = FUNC_OLD;
							goto old_proto;
						}
					}
					l = FUNC_NEW;
					if ((pt.t & VT_BTYPE) == VT_VOID && tok == ')') {
						break;
					}
					type_decl (&pt, &ad1, &n, TYPE_DIRECT | TYPE_ABSTRACT);
					if ((pt.t & VT_BTYPE) == VT_VOID) {
						TCC_ERR ("parameter declared as void");
					}
					arg_size += (type_size (&pt, &align) + PTR_SIZE - 1) / PTR_SIZE;
				} else {
old_proto:
					n = tok;
					if (n < TOK_UIDENT) {
						expect ("identifier");
					}
					pt.t = VT_INT32;
					next ();
				}
				convert_parameter_type (&pt);
				s = sym_push (n | SYM_FIELD, &pt, 0, 0);
				if (!s) {
					return;
				} else {
					char kind[1024];
					type_to_str (kind, sizeof (kind), &pt, NULL);
					tcc_appendf ("func.%s.arg.%d=%s,%s\n",
						symname, narg, kind, global_symname);
					narg++;
				}
				*plast = s;
				plast = &s->next;
				if (tok == ')') {
					break;
				}
				skip (',');
				if (l == FUNC_NEW && tok == TOK_DOTS) {
					l = FUNC_ELLIPSIS;
					next ();
					break;
				}
			}
		}
		tcc_appendf ("func.%s.args=%d\n", symname, narg);
		/* if no parameters, then old type prototype */
		if (l == 0) {
			l = FUNC_OLD;
		}
		skip (')');
		/* NOTE: const is ignored in returned type as it has a special
		   meaning in gcc / C++ */
		type->t &= ~VT_CONSTANT;
		/* some ancient pre-K&R C allows a function to return an array
		   and the array brackets to be put after the arguments, such
		   that "int c()[]" means something like "int[] c()" */
		if (tok == '[') {
			next ();
			skip (']');	/* only handle simple "[]" */
			type->t |= VT_PTR;
		}
		/* we push a anonymous symbol which will contain the function prototype */
		ad->func_args = arg_size;
		s = sym_push (SYM_FIELD, type, INT_ATTR (ad), l);
		if (!s) {
			return;
		}
		s->next = first;
		type->t = VT_FUNC;
		type->ref = s;
		R_FREE (symname);
	} else if (tok == '[') {
		/* array definition */
		next ();
		if (tok == TOK_RESTRICT1) {
			next ();
		}
		n = -1;
		t1 = 0;
		if (tok != ']') {
			if (!local_stack || nocode_wanted) {
				vpushll (expr_const ());
			} else {
				gexpr ();
			}
			if ((vtop->r & (VT_VALMASK | VT_LVAL | VT_SYM)) == VT_CONST) {
				n = vtop->c.i;
				if (n < 0) {
					TCC_ERR ("invalid array size");
				}
			} else {
				if (!is_integer_btype (vtop->type.t & VT_BTYPE)) {
					TCC_ERR ("size of variable length array should be an integer");
				}
				t1 = VT_VLA;
			}
		}
		skip (']');
		/* parse next post type */
		post_type (type, ad);

		/* we push an anonymous symbol which will contain the array
		   element type */
		arraysize = n;
#if 0
		if (n < 0) {
			printf ("array with no size []\n");
		} else {
			printf ("PUSH SIZE %d\n", n);
		}
#endif
		s = sym_push (SYM_FIELD, type, 0, n);
		if (!s) {
			return;
		}
		type->t = (t1? VT_VLA: VT_ARRAY) | VT_PTR;
		type->ref = s;
	}
}