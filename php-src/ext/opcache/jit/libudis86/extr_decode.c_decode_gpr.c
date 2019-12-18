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
struct ud {int dis_mode; int error; int /*<<< orphan*/  pfx_rex; } ;
typedef  enum ud_type { ____Placeholder_ud_type } ud_type ;

/* Variables and functions */
 int /*<<< orphan*/  UD_ASSERT (int) ; 
 int UD_NONE ; 
 int /*<<< orphan*/  UD_R_AL ; 
 int /*<<< orphan*/  UD_R_AX ; 
 int /*<<< orphan*/  UD_R_EAX ; 
 int /*<<< orphan*/  UD_R_RAX ; 
 int /*<<< orphan*/  UD_R_SPL ; 

__attribute__((used)) static enum ud_type 
decode_gpr(register struct ud* u, unsigned int s, unsigned char rm)
{
  switch (s) {
    case 64:
        return UD_R_RAX + rm;
    case 32:
        return UD_R_EAX + rm;
    case 16:
        return UD_R_AX  + rm;
    case  8:
        if (u->dis_mode == 64 && u->pfx_rex) {
            if (rm >= 4)
                return UD_R_SPL + (rm-4);
            return UD_R_AL + rm;
        } else return UD_R_AL + rm;
    case 0:
        /* invalid size in case of a decode error */
        UD_ASSERT(u->error);
        return UD_NONE;
    default:
        UD_ASSERT(!"invalid operand size");
        return UD_NONE;
  }
}