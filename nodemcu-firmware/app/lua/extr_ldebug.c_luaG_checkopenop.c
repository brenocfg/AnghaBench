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
typedef  int /*<<< orphan*/  Instruction ;

/* Variables and functions */
 int /*<<< orphan*/  GETARG_B (int /*<<< orphan*/ ) ; 
 int GET_OPCODE (int /*<<< orphan*/ ) ; 
#define  OP_CALL 131 
#define  OP_RETURN 130 
#define  OP_SETLIST 129 
#define  OP_TAILCALL 128 
 int /*<<< orphan*/  check (int) ; 

int luaG_checkopenop (Instruction i) {
  switch (GET_OPCODE(i)) {
    case OP_CALL:
    case OP_TAILCALL:
    case OP_RETURN:
    case OP_SETLIST: {
      check(GETARG_B(i) == 0);
      return 1;
    }
    default: return 0;  /* invalid instruction after an open call */
  }
}