#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {char const* member_0; size_t member_1; char const* member_2; size_t member_3; char const* member_4; size_t member_5; char* member_6; size_t member_7; int /*<<< orphan*/  member_8; } ;
typedef  TYPE_1__ crypto_op_t ;
struct TYPE_6__ {size_t block_size; int /*<<< orphan*/  (* run ) (TYPE_1__*) ;} ;
typedef  TYPE_2__ crypto_mech_t ;

/* Variables and functions */
 int /*<<< orphan*/  OP_DECRYPT ; 
 int /*<<< orphan*/  OP_ENCRYPT ; 
 TYPE_2__* get_mech (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 char* luaL_optlstring (int /*<<< orphan*/ *,int,char*,size_t*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_zalloc (size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static int crypto_encdec (lua_State *L, bool enc)
{
  const crypto_mech_t *mech = get_mech (L, 1);
  size_t klen;
  const char *key = luaL_checklstring (L, 2, &klen);
  size_t dlen;
  const char *data = luaL_checklstring (L, 3, &dlen);

  size_t ivlen;
  const char *iv = luaL_optlstring (L, 4, "", &ivlen);

  size_t bs = mech->block_size;
  size_t outlen = ((dlen + bs -1) / bs) * bs;
  char *buf = (char *)os_zalloc (outlen);
  if (!buf)
    return luaL_error (L, "crypto init failed");

  crypto_op_t op =
  {
    key, klen,
    iv, ivlen,
    data, dlen,
    buf, outlen,
    enc ? OP_ENCRYPT : OP_DECRYPT
  };
  if (!mech->run (&op))
  {
    os_free (buf);
    return luaL_error (L, "crypto op failed");
  }
  else
  {
    lua_pushlstring (L, buf, outlen);
    // note: if lua_pushlstring runs out of memory, we leak buf :(
    os_free (buf);
    return 1;
  }
}