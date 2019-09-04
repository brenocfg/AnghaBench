#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int /*<<< orphan*/  k_opad; TYPE_1__* mech_info; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_2__ digest_user_datum_t ;
struct TYPE_3__ {int /*<<< orphan*/  ctx_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaM_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaM_realloc_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypto_hash_gcdelete (lua_State *L)
{
  NODE_DBG("enter crypto_hash_delete.\n");
  digest_user_datum_t *dudat;

  dudat = (digest_user_datum_t *)luaL_checkudata(L, 1, "crypto.hash");

  // luaM_free() uses type info to obtain original size, so have to delve
  // one level deeper and explicitly pass the size due to void*
  luaM_realloc_ (L, dudat->ctx, dudat->mech_info->ctx_size, 0);
  luaM_free (L, dudat->k_opad);

  return 0;
}