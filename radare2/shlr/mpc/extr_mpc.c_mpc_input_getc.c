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
struct TYPE_6__ {size_t pos; } ;
struct TYPE_7__ {int type; char* string; int /*<<< orphan*/  file; int /*<<< orphan*/  buffer; TYPE_1__ state; } ;
typedef  TYPE_2__ mpc_input_t ;

/* Variables and functions */
#define  MPC_INPUT_FILE 130 
#define  MPC_INPUT_PIPE 129 
#define  MPC_INPUT_STRING 128 
 char fgetc (int /*<<< orphan*/ ) ; 
 char getc (int /*<<< orphan*/ ) ; 
 char mpc_input_buffer_get (TYPE_2__*) ; 
 int /*<<< orphan*/  mpc_input_buffer_in_range (TYPE_2__*) ; 

__attribute__((used)) static char mpc_input_getc(mpc_input_t *i) {
  
  char c = '\0';
  
  switch (i->type) {
    
    case MPC_INPUT_STRING: return i->string[i->state.pos];
    case MPC_INPUT_FILE: c = fgetc(i->file); return c;
    case MPC_INPUT_PIPE:
    
      if (!i->buffer) { c = getc(i->file); return c; }
      
      if (i->buffer && mpc_input_buffer_in_range(i)) {
        c = mpc_input_buffer_get(i);
        return c;
      } else {
        c = getc(i->file);
        return c;
      }
    
    default: return c;
  }
}