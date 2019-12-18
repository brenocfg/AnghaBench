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
struct TYPE_4__ {int server_pos; int last_server_pos; int /*<<< orphan*/  pcb; void* list_ref; void* err_cb_ref; void* sync_cb_ref; } ;
typedef  TYPE_1__ sntp_state_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  IP_ADDR_ANY ; 
 void* LUA_NOREF ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on_recv ; 
 TYPE_1__* state ; 
 scalar_t__ udp_bind (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udp_new () ; 
 int /*<<< orphan*/  udp_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *state_init(lua_State *L) {
  state = (sntp_state_t *)malloc (sizeof (sntp_state_t));
  if (!state)
    return ("out of memory");

  memset (state, 0, sizeof (sntp_state_t));

  state->sync_cb_ref = LUA_NOREF;
  state->err_cb_ref = LUA_NOREF;
  state->list_ref = LUA_NOREF;

  state->pcb = udp_new ();
  if (!state->pcb)
    return ("out of memory");

  if (udp_bind (state->pcb, IP_ADDR_ANY, 0) != ERR_OK)
    return ("no port available");

  udp_recv (state->pcb, on_recv, L);

  state->server_pos = -1;
  state->last_server_pos = -1;

  return NULL;
}