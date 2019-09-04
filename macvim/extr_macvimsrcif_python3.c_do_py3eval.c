#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  v_number; int /*<<< orphan*/  v_string; TYPE_2__* v_list; TYPE_1__* v_dict; } ;
struct TYPE_9__ {int v_type; TYPE_3__ vval; } ;
typedef  TYPE_4__ typval_T ;
typedef  int /*<<< orphan*/  runner ;
typedef  int /*<<< orphan*/  rangeinitializer ;
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_7__ {int /*<<< orphan*/  lv_refcount; } ;
struct TYPE_6__ {int /*<<< orphan*/  dv_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  DoPyCommand (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
#define  VAR_DICT 131 
#define  VAR_FUNC 130 
#define  VAR_LIST 129 
 int VAR_NUMBER ; 
#define  VAR_UNKNOWN 128 
 int /*<<< orphan*/  func_ref (int /*<<< orphan*/ ) ; 
 scalar_t__ init_range_eval ; 
 scalar_t__ run_eval ; 

void
do_py3eval (char_u *str, typval_T *rettv)
{
    DoPyCommand((char *) str,
	    (rangeinitializer) init_range_eval,
	    (runner) run_eval,
	    (void *) rettv);
    switch(rettv->v_type)
    {
	case VAR_DICT: ++rettv->vval.v_dict->dv_refcount; break;
	case VAR_LIST: ++rettv->vval.v_list->lv_refcount; break;
	case VAR_FUNC: func_ref(rettv->vval.v_string);    break;
	case VAR_UNKNOWN:
	    rettv->v_type = VAR_NUMBER;
	    rettv->vval.v_number = 0;
	    break;
    }
}