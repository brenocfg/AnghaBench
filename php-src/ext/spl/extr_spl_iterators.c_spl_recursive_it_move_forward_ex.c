#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_21__ {TYPE_1__* funcs; } ;
typedef  TYPE_2__ zend_object_iterator ;
struct TYPE_22__ {TYPE_2__* (* get_iterator ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ zend_class_entry ;
typedef  int /*<<< orphan*/  spl_sub_iterator ;
struct TYPE_23__ {size_t level; int flags; int max_depth; int const mode; TYPE_14__* iterators; scalar_t__ endChildren; TYPE_3__* ce; scalar_t__ beginChildren; scalar_t__ callGetChildren; scalar_t__ nextElement; scalar_t__ callHasChildren; } ;
typedef  TYPE_4__ spl_recursive_it_object ;
struct TYPE_20__ {int /*<<< orphan*/  (* rewind ) (TYPE_2__*) ;int /*<<< orphan*/  (* valid ) (TYPE_2__*) ;int /*<<< orphan*/  (* move_forward ) (TYPE_2__*) ;} ;
struct TYPE_19__ {int state; int /*<<< orphan*/  zobject; TYPE_3__* ce; TYPE_2__* iterator; } ;

/* Variables and functions */
 scalar_t__ EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  IS_OBJECT ; 
 int /*<<< orphan*/  IS_UNDEF ; 
 int RIT_CATCH_GET_CHILD ; 
#define  RIT_CHILD_FIRST 135 
#define  RIT_LEAVES_ONLY 134 
#define  RIT_SELF_FIRST 133 
#define  RS_CHILD 132 
#define  RS_NEXT 131 
#define  RS_SELF 130 
#define  RS_START 129 
#define  RS_TEST 128 
 int /*<<< orphan*/  SPL_FETCH_SUB_ITERATOR (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 TYPE_3__* Z_OBJCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_TYPE (int /*<<< orphan*/ ) ; 
 TYPE_14__* erealloc (TYPE_14__*,int) ; 
 int /*<<< orphan*/  exception ; 
 int /*<<< orphan*/  instanceof_function (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spl_ce_RecursiveIterator ; 
 int /*<<< orphan*/  spl_ce_UnexpectedValueException ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 TYPE_2__* stub3 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_call_method_with_0_params (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_clear_exception () ; 
 int zend_is_true (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_iterator_dtor (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_throw_exception (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_recursive_it_move_forward_ex(spl_recursive_it_object *object, zval *zthis)
{
	zend_object_iterator      *iterator;
	zval                      *zobject;
	zend_class_entry          *ce;
	zval                      retval, child;
	zend_object_iterator      *sub_iter;
	int                       has_children;

	SPL_FETCH_SUB_ITERATOR(iterator, object);

	while (!EG(exception)) {
next_step:
		iterator = object->iterators[object->level].iterator;
		switch (object->iterators[object->level].state) {
			case RS_NEXT:
				iterator->funcs->move_forward(iterator);
				if (EG(exception)) {
					if (!(object->flags & RIT_CATCH_GET_CHILD)) {
						return;
					} else {
						zend_clear_exception();
					}
				}
				/* fall through */
			case RS_START:
				if (iterator->funcs->valid(iterator) == FAILURE) {
					break;
				}
				object->iterators[object->level].state = RS_TEST;
				/* break; */
			case RS_TEST:
				ce = object->iterators[object->level].ce;
				zobject = &object->iterators[object->level].zobject;
				if (object->callHasChildren) {
					zend_call_method_with_0_params(Z_OBJ_P(zthis), object->ce, &object->callHasChildren, "callHasChildren", &retval);
				} else {
					zend_call_method_with_0_params(Z_OBJ_P(zobject), ce, NULL, "haschildren", &retval);
				}
				if (EG(exception)) {
					if (!(object->flags & RIT_CATCH_GET_CHILD)) {
						object->iterators[object->level].state = RS_NEXT;
						return;
					} else {
						zend_clear_exception();
					}
				}
				if (Z_TYPE(retval) != IS_UNDEF) {
					has_children = zend_is_true(&retval);
					zval_ptr_dtor(&retval);
					if (has_children) {
						if (object->max_depth == -1 || object->max_depth > object->level) {
							switch (object->mode) {
							case RIT_LEAVES_ONLY:
							case RIT_CHILD_FIRST:
								object->iterators[object->level].state = RS_CHILD;
								goto next_step;
							case RIT_SELF_FIRST:
								object->iterators[object->level].state = RS_SELF;
								goto next_step;
							}
						} else {
							/* do not recurse into */
							if (object->mode == RIT_LEAVES_ONLY) {
								/* this is not a leave, so skip it */
								object->iterators[object->level].state = RS_NEXT;
								goto next_step;
							}
						}
					}
				}
				if (object->nextElement) {
					zend_call_method_with_0_params(Z_OBJ_P(zthis), object->ce, &object->nextElement, "nextelement", NULL);
				}
				object->iterators[object->level].state = RS_NEXT;
				if (EG(exception)) {
					if (!(object->flags & RIT_CATCH_GET_CHILD)) {
						return;
					} else {
						zend_clear_exception();
					}
				}
				return /* self */;
			case RS_SELF:
				if (object->nextElement && (object->mode == RIT_SELF_FIRST || object->mode == RIT_CHILD_FIRST)) {
					zend_call_method_with_0_params(Z_OBJ_P(zthis), object->ce, &object->nextElement, "nextelement", NULL);
				}
				if (object->mode == RIT_SELF_FIRST) {
					object->iterators[object->level].state = RS_CHILD;
				} else {
					object->iterators[object->level].state = RS_NEXT;
				}
				return /* self */;
			case RS_CHILD:
				ce = object->iterators[object->level].ce;
				zobject = &object->iterators[object->level].zobject;
				if (object->callGetChildren) {
					zend_call_method_with_0_params(Z_OBJ_P(zthis), object->ce, &object->callGetChildren, "callGetChildren", &child);
				} else {
					zend_call_method_with_0_params(Z_OBJ_P(zobject), ce, NULL, "getchildren", &child);
				}

				if (EG(exception)) {
					if (!(object->flags & RIT_CATCH_GET_CHILD)) {
						return;
					} else {
						zend_clear_exception();
						zval_ptr_dtor(&child);
						object->iterators[object->level].state = RS_NEXT;
						goto next_step;
					}
				}

				if (Z_TYPE(child) == IS_UNDEF || Z_TYPE(child) != IS_OBJECT ||
						!((ce = Z_OBJCE(child)) && instanceof_function(ce, spl_ce_RecursiveIterator))) {
					zval_ptr_dtor(&child);
					zend_throw_exception(spl_ce_UnexpectedValueException, "Objects returned by RecursiveIterator::getChildren() must implement RecursiveIterator", 0);
					return;
				}

				if (object->mode == RIT_CHILD_FIRST) {
					object->iterators[object->level].state = RS_SELF;
				} else {
					object->iterators[object->level].state = RS_NEXT;
				}
				object->iterators = erealloc(object->iterators, sizeof(spl_sub_iterator) * (++object->level+1));
				sub_iter = ce->get_iterator(ce, &child, 0);
				ZVAL_COPY_VALUE(&object->iterators[object->level].zobject, &child);
				object->iterators[object->level].iterator = sub_iter;
				object->iterators[object->level].ce = ce;
				object->iterators[object->level].state = RS_START;
				if (sub_iter->funcs->rewind) {
					sub_iter->funcs->rewind(sub_iter);
				}
				if (object->beginChildren) {
					zend_call_method_with_0_params(Z_OBJ_P(zthis), object->ce, &object->beginChildren, "beginchildren", NULL);
					if (EG(exception)) {
						if (!(object->flags & RIT_CATCH_GET_CHILD)) {
							return;
						} else {
							zend_clear_exception();
						}
					}
				}
				goto next_step;
		}
		/* no more elements */
		if (object->level > 0) {
			if (object->endChildren) {
				zend_call_method_with_0_params(Z_OBJ_P(zthis), object->ce, &object->endChildren, "endchildren", NULL);
				if (EG(exception)) {
					if (!(object->flags & RIT_CATCH_GET_CHILD)) {
						return;
					} else {
						zend_clear_exception();
					}
				}
			}
			if (object->level > 0) {
				zval garbage;
				ZVAL_COPY_VALUE(&garbage, &object->iterators[object->level].zobject);
				ZVAL_UNDEF(&object->iterators[object->level].zobject);
				zval_ptr_dtor(&garbage);
				zend_iterator_dtor(iterator);
				object->level--;
			}
		} else {
			return; /* done completeley */
		}
	}
}