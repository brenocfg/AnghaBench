#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_4__ lua_State ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_14__ {TYPE_2__* p; } ;
struct TYPE_12__ {scalar_t__ isC; } ;
struct TYPE_16__ {TYPE_3__ l; TYPE_1__ c; } ;
struct TYPE_13__ {unsigned char* packedlineinfo; int* lineinfo; int sizelineinfo; } ;
typedef  TYPE_5__ Closure ;

/* Variables and functions */
 unsigned char INFO_DELTA_6BITS ; 
 unsigned char INFO_DELTA_7BITS ; 
 unsigned char INFO_DELTA_MASK ; 
 unsigned char INFO_FILL_BYTE ; 
 unsigned char INFO_SIGN_MASK ; 
 int /*<<< orphan*/  incr_top (TYPE_4__*) ; 
 int /*<<< orphan*/ * luaH_new (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaH_setnum (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setbvalue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sethvalue (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setnilvalue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void collectvalidlines (lua_State *L, Closure *f) {
   if (f == NULL || f->c.isC) {
     setnilvalue(L->top);
   }
   else {
  #  define INFO_FILL_BYTE   0x7F
#  define INFO_DELTA_MASK  0x80
#  define INFO_SIGN_MASK   0x40
#  define INFO_DELTA_6BITS 0x3F
#  define INFO_DELTA_7BITS 0x7F
#  define INFO_MAX_LINECNT  126

     Table *t = luaH_new(L, 0, 0);
#ifdef LUA_OPTIMIZE_DEBUG
    int line = 0;
    unsigned char *p = f->l.p->packedlineinfo;
    if (p) {
      for (; *p && *p != INFO_FILL_BYTE; ) {
        if (*p & INFO_DELTA_MASK) { /* line delta */
          int delta = *p & INFO_DELTA_6BITS;
          unsigned char sign = *p++ & INFO_SIGN_MASK;
          int shift;
          for (shift = 6; *p & INFO_DELTA_MASK; p++, shift += 7) {
            delta += (*p & INFO_DELTA_7BITS)<<shift;
          }
          line += sign ? -delta : delta+2;
        } else {
          line++;
        }
       p++;
       setbvalue(luaH_setnum(L, t, line), 1);
      }
    }
#else
     int *lineinfo = f->l.p->lineinfo;
     int i;
     for (i=0; i<f->l.p->sizelineinfo; i++)
       setbvalue(luaH_setnum(L, t, lineinfo[i]), 1);
#endif
     sethvalue(L, L->top, t);
   }
   incr_top(L);
 }