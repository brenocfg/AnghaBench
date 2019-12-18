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
 int EINVAL ; 
 int ENOMEM ; 
 int bad_file (int /*<<< orphan*/ *) ; 
 int bad_mech (int /*<<< orphan*/ *) ; 
 int bad_mem (int /*<<< orphan*/ *) ; 
 TYPE_1__* crypto_digest_mech (char*) ; 
 int crypto_fhash (TYPE_1__ const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vfs_close (int) ; 
 int vfs_open (char const*,char*) ; 
 int /*<<< orphan*/  vfs_read_wrap ; 

__attribute__((used)) static int crypto_flhash (lua_State *L)
{
  const digest_mech_info_t *mi = crypto_digest_mech (luaL_checkstring (L, 1));
  if (!mi)
    return bad_mech (L);
  const char *filename = luaL_checkstring (L, 2);

  // Open the file
  int file_fd = vfs_open (filename, "r");
  if(!file_fd) {
    return bad_file(L);
  }

  // Compute hash
  uint8_t digest[mi->digest_size];
  int returncode = crypto_fhash (mi, &vfs_read_wrap, file_fd, digest);

  // Finish up
  vfs_close(file_fd);

  if (returncode == ENOMEM)
    return bad_mem (L);
  else if (returncode == EINVAL)
    return bad_mech(L);
  else
    lua_pushlstring (L, digest, sizeof (digest));

  return 1;
}