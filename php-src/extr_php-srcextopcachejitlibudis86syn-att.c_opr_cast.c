#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ud_operand {int size; } ;
struct ud {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ud_asmprintf (struct ud*,char*) ; 

__attribute__((used)) static void 
opr_cast(struct ud* u, struct ud_operand* op)
{
  switch(op->size) {
  case 16 : case 32 :
    ud_asmprintf(u, "*");   break;
  default: break;
  }
}