#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int args; } ;
struct TYPE_6__ {TYPE_1__* op; } ;
struct TYPE_8__ {TYPE_3__ s_extended_operator; TYPE_2__ s_operator; } ;
struct demangle_component {int type; TYPE_4__ u; } ;
struct d_info {int /*<<< orphan*/  expansion; } ;
struct TYPE_5__ {char* code; int len; int args; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMANGLE_COMPONENT_BINARY ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_BINARY_ARGS ; 
#define  DEMANGLE_COMPONENT_CAST 130 
#define  DEMANGLE_COMPONENT_EXTENDED_OPERATOR 129 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_INITIALIZER_LIST ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_NULLARY ; 
#define  DEMANGLE_COMPONENT_OPERATOR 128 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_PACK_EXPANSION ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_QUAL_NAME ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_TEMPLATE ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_TRINARY ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_TRINARY_ARG1 ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_TRINARY_ARG2 ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_UNARY ; 
 int INT_MAX ; 
 scalar_t__ IS_DIGIT (char) ; 
 struct demangle_component* cplus_demangle_type (struct d_info*) ; 
 int /*<<< orphan*/  d_advance (struct d_info*,int) ; 
 int /*<<< orphan*/  d_check_char (struct d_info*,char) ; 
 int d_compact_number (struct d_info*) ; 
 struct demangle_component* d_expr_primary (struct d_info*) ; 
 struct demangle_component* d_exprlist (struct d_info*,char) ; 
 struct demangle_component* d_make_comp (struct d_info*,int /*<<< orphan*/ ,struct demangle_component*,struct demangle_component*) ; 
 struct demangle_component* d_make_function_param (struct d_info*,int) ; 
 struct demangle_component* d_operator_name (struct d_info*) ; 
 char d_peek_char (struct d_info*) ; 
 char d_peek_next_char (struct d_info*) ; 
 struct demangle_component* d_template_args (struct d_info*) ; 
 struct demangle_component* d_template_args_1 (struct d_info*) ; 
 struct demangle_component* d_template_param (struct d_info*) ; 
 struct demangle_component* d_unqualified_name (struct d_info*) ; 
 int /*<<< orphan*/  op_is_new_cast (struct demangle_component*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static inline struct demangle_component *
d_expression_1 (struct d_info *di)
{
  char peek;

  peek = d_peek_char (di);
  if (peek == 'L')
    return d_expr_primary (di);
  else if (peek == 'T')
    return d_template_param (di);
  else if (peek == 's' && d_peek_next_char (di) == 'r')
    {
      struct demangle_component *type;
      struct demangle_component *name;

      d_advance (di, 2);
      type = cplus_demangle_type (di);
      name = d_unqualified_name (di);
      if (d_peek_char (di) != 'I')
	return d_make_comp (di, DEMANGLE_COMPONENT_QUAL_NAME, type, name);
      else
	return d_make_comp (di, DEMANGLE_COMPONENT_QUAL_NAME, type,
			    d_make_comp (di, DEMANGLE_COMPONENT_TEMPLATE, name,
					 d_template_args (di)));
    }
  else if (peek == 's' && d_peek_next_char (di) == 'p')
    {
      d_advance (di, 2);
      return d_make_comp (di, DEMANGLE_COMPONENT_PACK_EXPANSION,
			  d_expression_1 (di), NULL);
    }
  else if (peek == 'f' && d_peek_next_char (di) == 'p')
    {
      /* Function parameter used in a late-specified return type.  */
      int index;
      d_advance (di, 2);
      if (d_peek_char (di) == 'T')
	{
	  /* 'this' parameter.  */
	  d_advance (di, 1);
	  index = 0;
	}
      else
	{
	  index = d_compact_number (di);
	  if (index == INT_MAX || index == -1)
	    return NULL;
	  index++;
	}
      return d_make_function_param (di, index);
    }
  else if (IS_DIGIT (peek)
	   || (peek == 'o' && d_peek_next_char (di) == 'n'))
    {
      /* We can get an unqualified name as an expression in the case of
         a dependent function call, i.e. decltype(f(t)).  */
      struct demangle_component *name;

      if (peek == 'o')
	/* operator-function-id, i.e. operator+(t).  */
	d_advance (di, 2);

      name = d_unqualified_name (di);
      if (name == NULL)
	return NULL;
      if (d_peek_char (di) == 'I')
	return d_make_comp (di, DEMANGLE_COMPONENT_TEMPLATE, name,
			    d_template_args (di));
      else
	return name;
    }
  else if ((peek == 'i' || peek == 't')
	   && d_peek_next_char (di) == 'l')
    {
      /* Brace-enclosed initializer list, untyped or typed.  */
      struct demangle_component *type = NULL;
      d_advance (di, 2);
      if (peek == 't')
	type = cplus_demangle_type (di);
      if (!d_peek_next_char (di))
	return NULL;
      return d_make_comp (di, DEMANGLE_COMPONENT_INITIALIZER_LIST,
			  type, d_exprlist (di, 'E'));
    }
  else
    {
      struct demangle_component *op;
      const char *code = NULL;
      int args;

      op = d_operator_name (di);
      if (op == NULL)
	return NULL;

      if (op->type == DEMANGLE_COMPONENT_OPERATOR)
	{
	  code = op->u.s_operator.op->code;
	  di->expansion += op->u.s_operator.op->len - 2;
	  if (strcmp (code, "st") == 0)
	    return d_make_comp (di, DEMANGLE_COMPONENT_UNARY, op,
				cplus_demangle_type (di));
	}

      switch (op->type)
	{
	default:
	  return NULL;
	case DEMANGLE_COMPONENT_OPERATOR:
	  args = op->u.s_operator.op->args;
	  break;
	case DEMANGLE_COMPONENT_EXTENDED_OPERATOR:
	  args = op->u.s_extended_operator.args;
	  break;
	case DEMANGLE_COMPONENT_CAST:
	  args = 1;
	  break;
	}

      switch (args)
	{
	case 0:
	  return d_make_comp (di, DEMANGLE_COMPONENT_NULLARY, op, NULL);

	case 1:
	  {
	    struct demangle_component *operand;
	    int suffix = 0;

	    if (code && (code[0] == 'p' || code[0] == 'm')
		&& code[1] == code[0])
	      /* pp_ and mm_ are the prefix variants.  */
	      suffix = !d_check_char (di, '_');

	    if (op->type == DEMANGLE_COMPONENT_CAST
		&& d_check_char (di, '_'))
	      operand = d_exprlist (di, 'E');
	    else if (code && !strcmp (code, "sP"))
	      operand = d_template_args_1 (di);
	    else
	      operand = d_expression_1 (di);

	    if (suffix)
	      /* Indicate the suffix variant for d_print_comp.  */
	      operand = d_make_comp (di, DEMANGLE_COMPONENT_BINARY_ARGS,
				     operand, operand);

	    return d_make_comp (di, DEMANGLE_COMPONENT_UNARY, op, operand);
	  }
	case 2:
	  {
	    struct demangle_component *left;
	    struct demangle_component *right;

	    if (code == NULL)
	      return NULL;
	    if (op_is_new_cast (op))
	      left = cplus_demangle_type (di);
	    else if (code[0] == 'f')
	      /* fold-expression.  */
	      left = d_operator_name (di);
	    else
	      left = d_expression_1 (di);
	    if (!strcmp (code, "cl"))
	      right = d_exprlist (di, 'E');
	    else if (!strcmp (code, "dt") || !strcmp (code, "pt"))
	      {
		right = d_unqualified_name (di);
		if (d_peek_char (di) == 'I')
		  right = d_make_comp (di, DEMANGLE_COMPONENT_TEMPLATE,
				       right, d_template_args (di));
	      }
	    else
	      right = d_expression_1 (di);

	    return d_make_comp (di, DEMANGLE_COMPONENT_BINARY, op,
				d_make_comp (di,
					     DEMANGLE_COMPONENT_BINARY_ARGS,
					     left, right));
	  }
	case 3:
	  {
	    struct demangle_component *first;
	    struct demangle_component *second;
	    struct demangle_component *third;

	    if (code == NULL)
	      return NULL;
	    else if (!strcmp (code, "qu"))
	      {
		/* ?: expression.  */
		first = d_expression_1 (di);
		second = d_expression_1 (di);
		third = d_expression_1 (di);
		if (third == NULL)
		  return NULL;
	      }
	    else if (code[0] == 'f')
	      {
		/* fold-expression.  */
		first = d_operator_name (di);
		second = d_expression_1 (di);
		third = d_expression_1 (di);
		if (third == NULL)
		  return NULL;
	      }
	    else if (code[0] == 'n')
	      {
		/* new-expression.  */
		if (code[1] != 'w' && code[1] != 'a')
		  return NULL;
		first = d_exprlist (di, '_');
		second = cplus_demangle_type (di);
		if (d_peek_char (di) == 'E')
		  {
		    d_advance (di, 1);
		    third = NULL;
		  }
		else if (d_peek_char (di) == 'p'
			 && d_peek_next_char (di) == 'i')
		  {
		    /* Parenthesized initializer.  */
		    d_advance (di, 2);
		    third = d_exprlist (di, 'E');
		  }
		else if (d_peek_char (di) == 'i'
			 && d_peek_next_char (di) == 'l')
		  /* initializer-list.  */
		  third = d_expression_1 (di);
		else
		  return NULL;
	      }
	    else
	      return NULL;
	    return d_make_comp (di, DEMANGLE_COMPONENT_TRINARY, op,
				d_make_comp (di,
					     DEMANGLE_COMPONENT_TRINARY_ARG1,
					     first,
					     d_make_comp (di,
							  DEMANGLE_COMPONENT_TRINARY_ARG2,
							  second, third)));
	  }
	default:
	  return NULL;
	}
    }
}