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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {int /*<<< orphan*/ * k_opad; void* ctx; TYPE_2__ const* mech_info; } ;
typedef  TYPE_1__ digest_user_datum_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* create ) (void*) ;int /*<<< orphan*/  ctx_size; int /*<<< orphan*/  block_size; } ;
typedef  TYPE_2__ digest_mech_info_t ;

/* Variables and functions */
 int WANT_HMAC ; 
 int bad_mech (int /*<<< orphan*/ *) ; 
 TYPE_2__* crypto_digest_mech (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_hmac_begin (void*,TYPE_2__ const*,char const*,size_t,int /*<<< orphan*/ *) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char*) ; 
 void* luaM_malloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static int crypto_new_hash_hmac (lua_State *L, int what)
{
  const digest_mech_info_t *mi = crypto_digest_mech (luaL_checkstring (L, 1));
  if (!mi)
    return bad_mech (L);

  size_t len = 0;
  const char *key = 0;
  uint8_t *k_opad = 0;
  if (what == WANT_HMAC)
  {
    key = luaL_checklstring (L, 2, &len);
    k_opad = luaM_malloc (L, mi->block_size);
  }
  void *ctx = luaM_malloc (L, mi->ctx_size);

  mi->create (ctx);

  if (what == WANT_HMAC)
    crypto_hmac_begin (ctx, mi, key, len, k_opad);

  // create a userdataum with specific metatable
  digest_user_datum_t *dudat = (digest_user_datum_t *)lua_newuserdata(L, sizeof(digest_user_datum_t));
  luaL_getmetatable(L, "crypto.hash");
  lua_setmetatable(L, -2);

  // Set pointers to the mechanics and CTX
  dudat->mech_info = mi;
  dudat->ctx       = ctx;
  dudat->k_opad    = k_opad;

  return 1; // Pass userdata object back
}