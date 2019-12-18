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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int end; int start; int buf; } ;
typedef  TYPE_1__ buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_TAIL ; 
 size_t INVALID_LEN ; 
 int LUAL_BUFFERSIZE ; 
 TYPE_1__* checkPipeTable (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 scalar_t__ lua_objlen (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  memcpy (int,char const*,size_t) ; 
 int /*<<< orphan*/  memmove (int,int,int) ; 
 TYPE_1__* newPipeUD (int /*<<< orphan*/ *,int,scalar_t__) ; 

__attribute__((used)) static int pipe_write(lua_State *L) {
  size_t l = INVALID_LEN;
  const char *s = lua_tolstring(L, 2, &l);
  if (l==0)
    return 0;
  luaL_argcheck(L, l != INVALID_LEN, 2, "must be a string");
  buffer_t *ud = checkPipeTable(L, 1, AT_TAIL);

  do {
    int used = ud->end - ud->start;

    if (used == LUAL_BUFFERSIZE) {
      ud = newPipeUD(L, 1, lua_objlen(L, 1)+1);
      used = 0;
    } else if (ud->start) {
      memmove(ud->buf, ud->buf + ud->start, used); /* must be memmove not cpy */
      ud->start = 0; ud->end = used;
    }

    int lrem = LUAL_BUFFERSIZE-used;
    if (l <= (unsigned )lrem)
      break;

    /* If we've got here then the remaining string is longer than the buffer */
    /* space left, so top off the buffer before looping around again */
    memcpy(ud->buf + ud->end, s, lrem);
    ud->end += lrem;
    l       -= lrem;
    s       += lrem;

  } while(1);

  /* Copy any residual tail to the UD buffer.  Note that this is l>0 and  */
  memcpy(ud->buf + ud->end, s, l);
  ud->end += l;
	return 0;
}