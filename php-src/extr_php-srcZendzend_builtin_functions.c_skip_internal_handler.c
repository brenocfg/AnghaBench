#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_6__* prev_execute_data; TYPE_2__* func; } ;
typedef  TYPE_7__ zend_execute_data ;
typedef  int zend_bool ;
struct TYPE_14__ {TYPE_5__* opline; TYPE_4__* func; } ;
struct TYPE_13__ {scalar_t__ opcode; } ;
struct TYPE_11__ {int /*<<< orphan*/  type; } ;
struct TYPE_12__ {TYPE_3__ common; } ;
struct TYPE_9__ {int /*<<< orphan*/  type; } ;
struct TYPE_10__ {TYPE_1__ common; } ;

/* Variables and functions */
 scalar_t__ ZEND_DO_FCALL ; 
 scalar_t__ ZEND_DO_FCALL_BY_NAME ; 
 scalar_t__ ZEND_DO_ICALL ; 
 scalar_t__ ZEND_DO_UCALL ; 
 scalar_t__ ZEND_INCLUDE_OR_EVAL ; 
 scalar_t__ ZEND_USER_CODE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline zend_bool skip_internal_handler(zend_execute_data *skip) /* {{{ */
{
	return !(skip->func && ZEND_USER_CODE(skip->func->common.type))
			&& skip->prev_execute_data
			&& skip->prev_execute_data->func
			&& ZEND_USER_CODE(skip->prev_execute_data->func->common.type)
			&& skip->prev_execute_data->opline->opcode != ZEND_DO_FCALL
			&& skip->prev_execute_data->opline->opcode != ZEND_DO_ICALL
			&& skip->prev_execute_data->opline->opcode != ZEND_DO_UCALL
			&& skip->prev_execute_data->opline->opcode != ZEND_DO_FCALL_BY_NAME
			&& skip->prev_execute_data->opline->opcode != ZEND_INCLUDE_OR_EVAL;
}