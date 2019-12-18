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
struct TYPE_4__ {scalar_t__ inflate_state; } ;
struct TYPE_3__ {char const* error; int /*<<< orphan*/  L; } ;

/* Variables and functions */
 TYPE_2__* in ; 
 int /*<<< orphan*/  lua_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ ) ; 
 TYPE_1__* out ; 
 int /*<<< orphan*/  uz_free (scalar_t__) ; 

__attribute__((used)) static void flash_error(const char *err) {
  if (out)
    out->error = err;
  if (in && in->inflate_state)
    uz_free(in->inflate_state);
  lua_pushnil(out->L);   /* can't use it on a cpcall anyway */
  lua_error(out->L);
}