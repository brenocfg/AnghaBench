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
struct jsonsl_state_st {int pos_cur; int pos_begin; } ;
typedef  int /*<<< orphan*/  luaL_Buffer ;
struct TYPE_4__ {int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ JSN_DATA ;

/* Variables and functions */
 int fromhex (char const) ; 
 char* get_state_buffer (TYPE_1__*,struct jsonsl_state_st*) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_putchar (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  output_utf8 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void push_string(JSN_DATA *data, struct jsonsl_state_st *state) {
  luaL_Buffer b;
  luaL_buffinit(data->L, &b);
  int i;
  const char *c = get_state_buffer(data, state) + 1;
  for (i = 0; i < state->pos_cur - state->pos_begin - 1; i++) {
    int nc = c[i];
    if (nc == '\\') {
      i++;
      nc = c[i] & 255;
      switch (c[i]) {
        case 'b':
          nc = '\b';
          break;
        case 'f':
          nc = '\f';
          break;
        case 'n':
          nc = '\n';
          break;
        case 'r':
          nc = '\r';
          break;
        case 't':
          nc = '\t';
          break;
        case 'u':
          nc = fromhex(c[++i]) << 12;
          nc += fromhex(c[++i]) << 8;
          nc += fromhex(c[++i]) << 4;
          nc += fromhex(c[++i])     ;
          output_utf8(&b, nc);
          continue;
      }
    }
    luaL_putchar(&b, nc);
  }
  luaL_pushresult(&b);
}