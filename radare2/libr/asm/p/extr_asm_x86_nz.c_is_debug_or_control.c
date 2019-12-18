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
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ Operand ;

/* Variables and functions */
 int OT_CONTROLREG ; 
 int OT_DEBUGREG ; 
 int OT_REGTYPE ; 

__attribute__((used)) static inline bool is_debug_or_control(Operand op) {
	return (op.type & OT_REGTYPE) & (OT_CONTROLREG | OT_DEBUGREG);
}