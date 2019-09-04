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
struct ud {int /*<<< orphan*/  asm_buf_int; int /*<<< orphan*/  mnemonic; } ;

/* Variables and functions */
 int /*<<< orphan*/  UD_Iinvalid ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  ud_set_asm_buffer (struct ud*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ud_set_input_file (struct ud*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ud_set_mode (struct ud*,int) ; 
 int /*<<< orphan*/  ud_set_pc (struct ud*,int /*<<< orphan*/ ) ; 

extern void 
ud_init(struct ud* u)
{
  memset((void*)u, 0, sizeof(struct ud));
  ud_set_mode(u, 16);
  u->mnemonic = UD_Iinvalid;
  ud_set_pc(u, 0);
#ifndef __UD_STANDALONE__
  ud_set_input_file(u, stdin);
#endif /* __UD_STANDALONE__ */

  ud_set_asm_buffer(u, u->asm_buf_int, sizeof(u->asm_buf_int));
}