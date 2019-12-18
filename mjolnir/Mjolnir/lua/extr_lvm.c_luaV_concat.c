#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  TString ;
typedef  int StkId ;

/* Variables and functions */
 size_t LUAI_MAXSHORTLEN ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  TM_CONCAT ; 
 int /*<<< orphan*/  cast_void (scalar_t__) ; 
 int /*<<< orphan*/  copy2buff (int,int,char*) ; 
 scalar_t__ cvt2str (int) ; 
 char* getstr (int /*<<< orphan*/ *) ; 
 scalar_t__ isemptystr (int) ; 
 int /*<<< orphan*/  luaG_runerror (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * luaS_createlngstrobj (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/ * luaS_newlstr (TYPE_1__*,char*,size_t) ; 
 int /*<<< orphan*/  luaT_trybinTM (TYPE_1__*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  setobjs2s (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  setsvalue2s (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ tostring (TYPE_1__*,int) ; 
 scalar_t__ ttisstring (int) ; 
 size_t vslen (int) ; 

void luaV_concat (lua_State *L, int total) {
  lua_assert(total >= 2);
  do {
    StkId top = L->top;
    int n = 2;  /* number of elements handled in this pass (at least 2) */
    if (!(ttisstring(top-2) || cvt2str(top-2)) || !tostring(L, top-1))
      luaT_trybinTM(L, top-2, top-1, top-2, TM_CONCAT);
    else if (isemptystr(top - 1))  /* second operand is empty? */
      cast_void(tostring(L, top - 2));  /* result is first operand */
    else if (isemptystr(top - 2)) {  /* first operand is an empty string? */
      setobjs2s(L, top - 2, top - 1);  /* result is second op. */
    }
    else {
      /* at least two non-empty string values; get as many as possible */
      size_t tl = vslen(top - 1);
      TString *ts;
      /* collect total length and number of strings */
      for (n = 1; n < total && tostring(L, top - n - 1); n++) {
        size_t l = vslen(top - n - 1);
        if (l >= (MAX_SIZE/sizeof(char)) - tl)
          luaG_runerror(L, "string length overflow");
        tl += l;
      }
      if (tl <= LUAI_MAXSHORTLEN) {  /* is result a short string? */
        char buff[LUAI_MAXSHORTLEN];
        copy2buff(top, n, buff);  /* copy strings to buffer */
        ts = luaS_newlstr(L, buff, tl);
      }
      else {  /* long string; copy strings directly to final result */
        ts = luaS_createlngstrobj(L, tl);
        copy2buff(top, n, getstr(ts));
      }
      setsvalue2s(L, top - n, ts);  /* create result */
    }
    total -= n-1;  /* got 'n' strings to create 1 new */
    L->top -= n-1;  /* popped 'n' strings and pushed one */
  } while (total > 1);  /* repeat until only 1 result left */
}