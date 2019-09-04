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
typedef  int uint8_t ;
struct ud {scalar_t__ inp_ctr; int pfx_adr; int pfx_lock; int pfx_opr; int pfx_str; int dis_mode; int pfx_rex; int /*<<< orphan*/  pfx_seg; } ;

/* Variables and functions */
 scalar_t__ MAX_INSN_LENGTH ; 
 int /*<<< orphan*/  UD_RETURN_ON_ERROR (struct ud*) ; 
 int /*<<< orphan*/  UD_RETURN_WITH_ERROR (struct ud*,char*) ; 
 int /*<<< orphan*/  UD_R_CS ; 
 int /*<<< orphan*/  UD_R_DS ; 
 int /*<<< orphan*/  UD_R_ES ; 
 int /*<<< orphan*/  UD_R_FS ; 
 int /*<<< orphan*/  UD_R_GS ; 
 int /*<<< orphan*/  UD_R_SS ; 
 int inp_next (struct ud*) ; 

__attribute__((used)) static int 
decode_prefixes(struct ud *u)
{
  int done = 0;
  uint8_t curr = 0, last = 0;
  UD_RETURN_ON_ERROR(u);

  do {
    last = curr;
    curr = inp_next(u); 
    UD_RETURN_ON_ERROR(u);
    if (u->inp_ctr == MAX_INSN_LENGTH) {
      UD_RETURN_WITH_ERROR(u, "max instruction length");
    }
   
    switch (curr)  
    {
    case 0x2E: 
      u->pfx_seg = UD_R_CS; 
      break;
    case 0x36:     
      u->pfx_seg = UD_R_SS; 
      break;
    case 0x3E: 
      u->pfx_seg = UD_R_DS; 
      break;
    case 0x26: 
      u->pfx_seg = UD_R_ES; 
      break;
    case 0x64: 
      u->pfx_seg = UD_R_FS; 
      break;
    case 0x65: 
      u->pfx_seg = UD_R_GS; 
      break;
    case 0x67: /* adress-size override prefix */ 
      u->pfx_adr = 0x67;
      break;
    case 0xF0: 
      u->pfx_lock = 0xF0;
      break;
    case 0x66: 
      u->pfx_opr = 0x66;
      break;
    case 0xF2:
      u->pfx_str = 0xf2;
      break;
    case 0xF3:
      u->pfx_str = 0xf3;
      break;
    default:
      /* consume if rex */
      done = (u->dis_mode == 64 && (curr & 0xF0) == 0x40) ? 0 : 1;
      break;
    }
  } while (!done);
  /* rex prefixes in 64bit mode, must be the last prefix */
  if (u->dis_mode == 64 && (last & 0xF0) == 0x40) {
    u->pfx_rex = last;  
  }
  return 0;
}