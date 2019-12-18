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
struct TYPE_4__ {int type; int /*<<< orphan*/  file; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ mpc_input_t ;

/* Variables and functions */
#define  MPC_INPUT_FILE 130 
#define  MPC_INPUT_PIPE 129 
#define  MPC_INPUT_STRING 128 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc_input_buffer_in_range (TYPE_1__*) ; 
 int /*<<< orphan*/  ungetc (char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpc_input_failure(mpc_input_t *i, char c) {

  switch (i->type) {
    case MPC_INPUT_STRING: { break; }
    case MPC_INPUT_FILE: fseek(i->file, -1, SEEK_CUR); { break; }
    case MPC_INPUT_PIPE: {
      
      if (!i->buffer) { ungetc(c, i->file); break; }
      
      if (i->buffer && mpc_input_buffer_in_range(i)) {
        break;
      } else {
        ungetc(c, i->file); 
      }
    }
    default: { break; }
  }
  return 0;
}