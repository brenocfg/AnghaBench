#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  row; scalar_t__ col; int /*<<< orphan*/  pos; } ;
struct TYPE_7__ {scalar_t__ type; char* buffer; char last; TYPE_1__ state; } ;
typedef  TYPE_2__ mpc_input_t ;

/* Variables and functions */
 scalar_t__ MPC_INPUT_PIPE ; 
 int /*<<< orphan*/  mpc_input_buffer_in_range (TYPE_2__*) ; 
 char* mpc_malloc (TYPE_2__*,int) ; 
 char* realloc (char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static int mpc_input_success(mpc_input_t *i, char c, char **o) {
  
  if (i->type == MPC_INPUT_PIPE
  &&  i->buffer && !mpc_input_buffer_in_range(i)) {
    i->buffer = realloc(i->buffer, strlen(i->buffer) + 2);
    i->buffer[strlen(i->buffer) + 1] = '\0';
    i->buffer[strlen(i->buffer) + 0] = c;
  }
  
  i->last = c;
  i->state.pos++;
  i->state.col++;
  
  if (c == '\n') {
    i->state.col = 0;
    i->state.row++;
  }
  
  if (o) {
    (*o) = mpc_malloc(i, 2);
    (*o)[0] = c;
    (*o)[1] = '\0';
  }
  
  return 1;
}