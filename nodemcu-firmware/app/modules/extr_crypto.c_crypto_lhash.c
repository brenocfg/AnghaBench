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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int digest_size; } ;
typedef  TYPE_1__ digest_mech_info_t ;
typedef  int /*<<< orphan*/  digest ;

/* Variables and functions */
 int bad_mech (int /*<<< orphan*/ *) ; 
 int bad_mem (int /*<<< orphan*/ *) ; 
 TYPE_1__* crypto_digest_mech (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_hash (TYPE_1__ const*,char const*,size_t,int /*<<< orphan*/ *) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int crypto_lhash (lua_State *L)
{
  const digest_mech_info_t *mi = crypto_digest_mech (luaL_checkstring (L, 1));
  if (!mi)
    return bad_mech (L);
  size_t len = 0;
  const char *data = luaL_checklstring (L, 2, &len);

  uint8_t digest[mi->digest_size];
  if (crypto_hash (mi, data, len, digest) != 0)
    return bad_mem (L);

  lua_pushlstring (L, digest, sizeof (digest));
  return 1;
}