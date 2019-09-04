#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char last; } ;
typedef  TYPE_1__ mpc_input_t ;

/* Variables and functions */
 char mpc_input_peekc (TYPE_1__*) ; 

__attribute__((used)) static int mpc_input_anchor(mpc_input_t* i, int(*f)(char,char), char **o) {
  *o = NULL;
  return f(i->last, mpc_input_peekc(i));
}