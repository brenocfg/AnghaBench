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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {scalar_t__ fd; int /*<<< orphan*/  flagsLen; scalar_t__ flags; struct TYPE_4__** block; } ;

/* Variables and functions */
 int WRITE_BLOCKS ; 
 TYPE_1__* in ; 
 int /*<<< orphan*/  luaM_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  luaM_freearray (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* out ; 
 int /*<<< orphan*/  uint32_t ; 
 int /*<<< orphan*/  vfs_close (scalar_t__) ; 

__attribute__((used)) static int loadLFSgc (lua_State *L) {
  int i;
  if (out) {
    for (i = 0; i < WRITE_BLOCKS; i++)
      if (out->block[i])
        luaM_free(L, out->block[i]);
    if (out->flags)
      luaM_freearray(L, out->flags, out->flagsLen, uint32_t);
    luaM_free(L, out);
  }
  if (in) {
    if (in->fd)
      vfs_close(in->fd);
    luaM_free(L, in);
  }
  return 0;
}