#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pc; TYPE_1__* f; } ;
struct TYPE_4__ {int* lineinfo; } ;
typedef  TYPE_2__ FuncState ;

/* Variables and functions */

void luaK_fixline (FuncState *fs, int line) {
#ifdef LUA_OPTIMIZE_DEBUG
  /* The fixup line can be the same as existing one and in this case there's nothing to do */
  if (line != fs->lastline) {
    /* first remove the current line reference */
    unsigned char *p = lineInfoTop(fs);
    lua_assert(*p < 127);
    if (*p >1) {
      (*p)--;    /* this is simply decrementing the last count a multi-PC line */
    } else {
      /* it's a bit more complicated if it's the 1st instruction on the line */
      int delta = 0;
      unsigned char code;
      /* this logic handles <i/c> [1snnnnnnn [1nnnnnnn]*]? <i/c=1> */
      *p-- = INFO_FILL_BYTE;
      /* work backwards over the coded delta computing the delta */
      while ((code=*p) & INFO_DELTA_MASK) {
        *p-- = INFO_FILL_BYTE;
        if (*p & INFO_DELTA_MASK) {
          delta = delta + ((code & INFO_DELTA_7BITS)<<7);
        } else {
          delta += (code & INFO_DELTA_6BITS) + 1;
          if (code & INFO_SIGN_MASK) delta = -delta;
        }
      }
      /* and reposition the FuncState lastline pointers at the previous instruction count */
      fs->lastline-= delta + 1;
      fs->lastlineOffset = p - fs->f->packedlineinfo;
    }
    /* Then add the new line reference */
    generateInfoDeltaLine(fs, line);
  }
#else
   fs->f->lineinfo[fs->pc - 1] = line;
#endif
}