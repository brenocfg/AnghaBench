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
struct ud {char* asm_buf; int /*<<< orphan*/  (* translator ) (struct ud*) ;scalar_t__ inp_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ud*) ; 
 int ud_decode (struct ud*) ; 

extern unsigned int
ud_disassemble(struct ud* u)
{
  int len;
  if (u->inp_end) {
    return 0;
  }
  if ((len = ud_decode(u)) > 0) {
    if (u->translator != NULL) {
      u->asm_buf[0] = '\0';
      u->translator(u);
    }
  }
  return len;
}