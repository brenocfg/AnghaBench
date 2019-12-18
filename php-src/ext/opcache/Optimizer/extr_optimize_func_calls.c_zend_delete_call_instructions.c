#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  var; } ;
struct TYPE_6__ {int opcode; TYPE_1__ result; int /*<<< orphan*/  extended_value; int /*<<< orphan*/  op1_type; } ;
typedef  TYPE_2__ zend_op ;

/* Variables and functions */
 int /*<<< orphan*/  IS_CONST ; 
 int /*<<< orphan*/  IS_CV ; 
 int /*<<< orphan*/  MAKE_NOP (TYPE_2__*) ; 
 int ZEND_CHECK_VAR ; 
#define  ZEND_DO_FCALL 141 
#define  ZEND_DO_FCALL_BY_NAME 140 
#define  ZEND_DO_ICALL 139 
#define  ZEND_DO_UCALL 138 
 int ZEND_FREE ; 
#define  ZEND_INIT_DYNAMIC_CALL 137 
#define  ZEND_INIT_FCALL 136 
#define  ZEND_INIT_FCALL_BY_NAME 135 
#define  ZEND_INIT_METHOD_CALL 134 
#define  ZEND_INIT_NS_FCALL_BY_NAME 133 
#define  ZEND_INIT_STATIC_METHOD_CALL 132 
#define  ZEND_INIT_USER_CALL 131 
#define  ZEND_NEW 130 
#define  ZEND_SEND_VAL 129 
#define  ZEND_SEND_VAR 128 

__attribute__((used)) static void zend_delete_call_instructions(zend_op *opline)
{
	int call = 0;

	while (1) {
		switch (opline->opcode) {
			case ZEND_INIT_FCALL_BY_NAME:
			case ZEND_INIT_NS_FCALL_BY_NAME:
			case ZEND_INIT_STATIC_METHOD_CALL:
			case ZEND_INIT_METHOD_CALL:
			case ZEND_INIT_FCALL:
				if (call == 0) {
					MAKE_NOP(opline);
					return;
				}
				/* break missing intentionally */
			case ZEND_NEW:
			case ZEND_INIT_DYNAMIC_CALL:
			case ZEND_INIT_USER_CALL:
				call--;
				break;
			case ZEND_DO_FCALL:
			case ZEND_DO_ICALL:
			case ZEND_DO_UCALL:
			case ZEND_DO_FCALL_BY_NAME:
				call++;
				break;
			case ZEND_SEND_VAL:
			case ZEND_SEND_VAR:
				if (call == 0) {
					if (opline->op1_type == IS_CONST) {
						MAKE_NOP(opline);
					} else if (opline->op1_type == IS_CV) {
						opline->opcode = ZEND_CHECK_VAR;
						opline->extended_value = 0;
						opline->result.var = 0;
					} else {
						opline->opcode = ZEND_FREE;
						opline->extended_value = 0;
						opline->result.var = 0;
					}
				}
				break;
		}
		opline--;
	}
}