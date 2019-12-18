#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {char const* buff; int /*<<< orphan*/  f; scalar_t__ extraline; } ;
typedef  TYPE_1__ LoadFSF ;

/* Variables and functions */
 scalar_t__ vfs_eof (int /*<<< orphan*/ ) ; 
 size_t vfs_read (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static const char *getFSF (lua_State *L, void *ud, size_t *size) {
  LoadFSF *lf = (LoadFSF *)ud;
  (void)L;

  if (L == NULL && size == NULL) // Direct mode check
    return NULL;

  if (lf->extraline) {
    lf->extraline = 0;
    *size = 1;
    return "\n";
  }

  if (vfs_eof(lf->f)) return NULL;
  *size = vfs_read(lf->f, lf->buff, sizeof(lf->buff));

  return (*size > 0) ? lf->buff : NULL;
}