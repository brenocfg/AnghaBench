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
struct ud {scalar_t__ br_far; } ;

/* Variables and functions */
 int /*<<< orphan*/  ud_asmprintf (struct ud*,char*) ; 

__attribute__((used)) static void 
opr_cast(struct ud* u, struct ud_operand* op)
{
  if (u->br_far) {
    ud_asmprintf(u, "far "); 
  }
  switch(op->size) {
  case  8:  ud_asmprintf(u, "byte " ); break;
  case 16:  ud_asmprintf(u, "word " ); break;
  case 32:  ud_asmprintf(u, "dword "); break;
  case 64:  ud_asmprintf(u, "qword "); break;
  case 80:  ud_asmprintf(u, "tword "); break;
  case 128: ud_asmprintf(u, "oword "); break;
  case 256: ud_asmprintf(u, "yword "); break;
  default: break;
  }
}