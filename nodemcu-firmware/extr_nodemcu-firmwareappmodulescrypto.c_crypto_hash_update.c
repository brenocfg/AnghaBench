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
struct TYPE_3__ {int /*<<< orphan*/  ctx; TYPE_2__* mech_info; } ;
typedef  TYPE_1__ digest_user_datum_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ ,char const*,size_t) ;} ;
typedef  TYPE_2__ digest_mech_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static int crypto_hash_update (lua_State *L)
{
  NODE_DBG("enter crypto_hash_update.\n");
  digest_user_datum_t *dudat;
  size_t sl;

  dudat = (digest_user_datum_t *)luaL_checkudata(L, 1, "crypto.hash");

  const digest_mech_info_t *mi = dudat->mech_info;

  size_t len = 0;
  const char *data = luaL_checklstring (L, 2, &len);

  mi->update (dudat->ctx, data, len);

  return 0;  // No return value
}