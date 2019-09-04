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
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int luaL_error (int /*<<< orphan*/ *,char*,scalar_t__,...) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static uint64_t lcron_parsepart(lua_State *L, char *str, char **end, uint8_t min, uint8_t max) {
  uint64_t res = 0;

  /* Gobble whitespace before potential stars; no strtol on that path */
  while (*str != '\0' && (*str == ' ' || *str == '\t')) {
    str++;
  }

  if (str[0] == '*') {
    uint32_t each = 1;
    *end = str + 1;
    if (str[1] == '/') {
      each = strtol(str + 2, end, 10);
      if (each == 0 || each >= max - min) {
        return luaL_error(L, "invalid spec (each %d)", each);
      }
    }
    for (int i = 0; i <= (max - min); i++) {
      if ((i % each) == 0) res |= (uint64_t)1 << i;
    }
  } else {
    uint32_t val;
    while (1) {
      val = strtol(str, end, 10);
      if (val < min || val > max) {
        return luaL_error(L, "invalid spec (val %d out of range %d..%d)", val, min, max);
      }
      res |= (uint64_t)1 << (val - min);
      if (**end != ',') break;
      str = *end + 1;
    }
  }
  return res;
}