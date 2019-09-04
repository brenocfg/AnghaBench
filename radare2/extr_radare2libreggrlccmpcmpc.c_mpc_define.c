#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; int /*<<< orphan*/  type; scalar_t__ retained; } ;
typedef  TYPE_1__ mpc_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* mpc_failf (char*) ; 

mpc_parser_t *mpc_define(mpc_parser_t *p, mpc_parser_t *a) {
  
  if (p->retained) {
    p->type = a->type;
    p->data = a->data;
  } else {
    mpc_parser_t *a2 = mpc_failf("Attempt to assign to Unretained Parser!");
    p->type = a2->type;
    p->data = a2->data;
    free(a2);
  }
  
  free(a);
  return p;  
}