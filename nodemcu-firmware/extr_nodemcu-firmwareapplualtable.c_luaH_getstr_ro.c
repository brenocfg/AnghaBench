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
struct TYPE_5__ {scalar_t__ len; } ;
struct TYPE_6__ {TYPE_1__ tsv; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_2__ TString ;

/* Variables and functions */
 scalar_t__ LUA_MAX_ROTABLE_NAME ; 
 int /*<<< orphan*/  const* luaO_nilobject ; 
 int /*<<< orphan*/  const* luaR_findentry (void*,TYPE_2__*,int /*<<< orphan*/ *) ; 

const TValue *luaH_getstr_ro (void *t, TString *key) {
  if (!t || key->tsv.len>LUA_MAX_ROTABLE_NAME)
    return luaO_nilobject;
  return luaR_findentry(t, key, NULL);
}