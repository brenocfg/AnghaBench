#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* op; } ;
struct TYPE_6__ {TYPE_2__ s_operator; } ;
struct demangle_component {scalar_t__ type; TYPE_3__ u; } ;
struct d_info {int /*<<< orphan*/  expansion; } ;
struct TYPE_4__ {int len; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 scalar_t__ DEMANGLE_COMPONENT_OPERATOR ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_UNARY ; 
 scalar_t__ IS_DIGIT (char) ; 
 scalar_t__ IS_LOWER (char) ; 
 struct demangle_component* d_abi_tags (struct d_info*,struct demangle_component*) ; 
 int /*<<< orphan*/  d_advance (struct d_info*,int) ; 
 struct demangle_component* d_ctor_dtor_name (struct d_info*) ; 
 int /*<<< orphan*/  d_discriminator (struct d_info*) ; 
 struct demangle_component* d_lambda (struct d_info*) ; 
 struct demangle_component* d_make_comp (struct d_info*,int /*<<< orphan*/ ,struct demangle_component*,struct demangle_component*) ; 
 struct demangle_component* d_operator_name (struct d_info*) ; 
 char d_peek_char (struct d_info*) ; 
 char d_peek_next_char (struct d_info*) ; 
 struct demangle_component* d_source_name (struct d_info*) ; 
 struct demangle_component* d_unnamed_type (struct d_info*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct demangle_component *
d_unqualified_name (struct d_info *di)
{
  struct demangle_component *ret;
  char peek;

  peek = d_peek_char (di);
  if (IS_DIGIT (peek))
    ret = d_source_name (di);
  else if (IS_LOWER (peek))
    {
      if (peek == 'o' && d_peek_next_char (di) == 'n')
	d_advance (di, 2);
      ret = d_operator_name (di);
      if (ret != NULL && ret->type == DEMANGLE_COMPONENT_OPERATOR)
	{
	  di->expansion += sizeof "operator" + ret->u.s_operator.op->len - 2;
	  if (!strcmp (ret->u.s_operator.op->code, "li"))
	    ret = d_make_comp (di, DEMANGLE_COMPONENT_UNARY, ret,
			       d_source_name (di));
	}
    }
  else if (peek == 'C' || peek == 'D')
    ret = d_ctor_dtor_name (di);
  else if (peek == 'L')
    {
      d_advance (di, 1);

      ret = d_source_name (di);
      if (ret == NULL)
	return NULL;
      if (! d_discriminator (di))
	return NULL;
    }
  else if (peek == 'U')
    {
      switch (d_peek_next_char (di))
	{
	case 'l':
	  ret = d_lambda (di);
	  break;
	case 't':
	  ret = d_unnamed_type (di);
	  break;
	default:
	  return NULL;
	}
    }
  else
    return NULL;

  if (d_peek_char (di) == 'B')
    ret = d_abi_tags (di, ret);
  return ret;
}