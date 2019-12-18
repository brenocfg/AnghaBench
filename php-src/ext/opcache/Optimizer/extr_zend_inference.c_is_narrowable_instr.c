#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ opcode; } ;
typedef  TYPE_1__ zend_op ;
typedef  int zend_bool ;

/* Variables and functions */
 scalar_t__ ZEND_ADD ; 
 scalar_t__ ZEND_DIV ; 
 scalar_t__ ZEND_MUL ; 
 scalar_t__ ZEND_SUB ; 

__attribute__((used)) static zend_bool is_narrowable_instr(zend_op *opline)  {
	return opline->opcode == ZEND_ADD || opline->opcode == ZEND_SUB
		|| opline->opcode == ZEND_MUL || opline->opcode == ZEND_DIV;
}