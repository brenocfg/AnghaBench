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
struct TYPE_4__ {scalar_t__ type; struct TYPE_4__* lasts; struct TYPE_4__* marks; struct TYPE_4__* buffer; struct TYPE_4__* string; struct TYPE_4__* filename; } ;
typedef  TYPE_1__ mpc_input_t ;

/* Variables and functions */
 scalar_t__ MPC_INPUT_PIPE ; 
 scalar_t__ MPC_INPUT_STRING ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void mpc_input_delete(mpc_input_t *i) {
  
  free(i->filename);
  
  if (i->type == MPC_INPUT_STRING) { free(i->string); }
  if (i->type == MPC_INPUT_PIPE) { free(i->buffer); }
  
  free(i->marks);
  free(i->lasts);
  free(i);
}