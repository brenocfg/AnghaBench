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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ luaM_malloc (int /*<<< orphan*/ *,size_t) ; 
 void* to_hex_nibble (int const) ; 

__attribute__((used)) static uint8 *toHex ( lua_State* L, const uint8 *msg, size_t *len){
  int i, n = *len;
  *len <<= 1;
  uint8 *q, *out = (uint8 *)luaM_malloc(L, *len);
  for (i = 0, q = out; i < n; i++) {
    *q++ = to_hex_nibble(msg[i] >> 4);
    *q++ = to_hex_nibble(msg[i] & 0xf);
  }
  return out;
}