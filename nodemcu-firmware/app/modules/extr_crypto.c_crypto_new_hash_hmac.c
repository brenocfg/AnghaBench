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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {char* k_opad; void* ctx; TYPE_2__ const* mech_info; } ;
typedef  TYPE_1__ digest_user_datum_t ;
struct TYPE_6__ {size_t block_size; int ctx_size; int /*<<< orphan*/  (* create ) (void*) ;} ;
typedef  TYPE_2__ digest_mech_info_t ;

/* Variables and functions */
 int WANT_HMAC ; 
 int bad_mech (int /*<<< orphan*/ *) ; 
 TYPE_2__* crypto_digest_mech (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_hmac_begin (void*,TYPE_2__ const*,char const*,size_t,char*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static int crypto_new_hash_hmac (lua_State *L, int what)
{
  // get pointer to relevant hash_mechs table entry in app/crypto/digest.c.  Note that
  // the size of the table needed is dependent on the the digest type
  const digest_mech_info_t *mi = crypto_digest_mech (luaL_checkstring (L, 1));
  if (!mi)
    return bad_mech (L);

  size_t len = 0, k_opad_len = 0, udlen;
  const char *key = NULL;
  uint8_t *k_opad = NULL;

  if (what == WANT_HMAC)
  { // The key and k_opad are only used for HMAC; these default to NULLs for HASH
    key = luaL_checklstring (L, 2, &len);
    k_opad_len = mi->block_size;
  }

  // create a userdatum with specific metatable.  This comprises the ud header, 
  // the encrypto context block, and an optional HMAC block as a single allocation
  // unit
  udlen = sizeof(digest_user_datum_t) + mi->ctx_size + k_opad_len;
  digest_user_datum_t *dudat = (digest_user_datum_t *)lua_newuserdata(L, udlen);
  luaL_getmetatable(L, "crypto.hash");  // and set its metatable to the crypto.hash table
  lua_setmetatable(L, -2);

  void *ctx = dudat + 1;  // The context block immediately follows the digest_user_datum
  mi->create (ctx);
  
  if (what == WANT_HMAC) {
    // The k_opad block immediately follows the context block
    k_opad = (char *)ctx + mi->ctx_size; 
    crypto_hmac_begin (ctx, mi, key, len, k_opad);
  }

  // Set pointers to the mechanics and CTX
  dudat->mech_info = mi;
  dudat->ctx       = ctx;
  dudat->k_opad    = k_opad;

  return 1; // Pass userdata object back
}