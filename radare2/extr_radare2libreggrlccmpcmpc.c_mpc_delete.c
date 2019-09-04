#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; struct TYPE_5__* name; scalar_t__ retained; } ;
typedef  TYPE_1__ mpc_parser_t ;

/* Variables and functions */
 scalar_t__ MPC_TYPE_UNDEFINED ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  mpc_undefine_unretained (TYPE_1__*,int /*<<< orphan*/ ) ; 

void mpc_delete(mpc_parser_t *p) {
  if (p->retained) {

    if (p->type != MPC_TYPE_UNDEFINED) {
      mpc_undefine_unretained(p, 0);
    } 
    
    free(p->name);
    free(p);
  
  } else {
    mpc_undefine_unretained(p, 0);  
  }
}