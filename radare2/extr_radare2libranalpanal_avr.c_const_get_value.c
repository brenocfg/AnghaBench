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
typedef  int ut32 ;
struct TYPE_3__ {int size; int value; } ;
typedef  TYPE_1__ CPU_CONST ;

/* Variables and functions */
 int MASK (int) ; 

__attribute__((used)) static ut32 const_get_value(CPU_CONST *c) {
	return c ? MASK (c->size * 8) & c->value : 0;
}