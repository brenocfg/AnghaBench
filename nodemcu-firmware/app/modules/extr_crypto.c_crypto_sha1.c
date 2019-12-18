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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,char const*,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int crypto_sha1( lua_State* L )
{
  SHA1_CTX ctx;
  uint8_t digest[20];
  // Read the string from lua (with length)
  int len;
  const char* msg = luaL_checklstring(L, 1, &len);
  // Use the SHA* functions in the rom
  SHA1Init(&ctx);
  SHA1Update(&ctx, msg, len);
  SHA1Final(digest, &ctx);

  // Push the result as a lua string
  lua_pushlstring(L, digest, 20);
  return 1;
}