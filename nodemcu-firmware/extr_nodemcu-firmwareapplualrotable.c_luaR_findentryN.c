#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ luaR_numkey ;
struct TYPE_6__ {scalar_t__ numkey; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_1__ id; } ;
struct TYPE_8__ {int /*<<< orphan*/  const value; TYPE_2__ key; } ;
typedef  TYPE_3__ luaR_entry ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_3__ ROTable ;

/* Variables and functions */
 scalar_t__ LUA_TNIL ; 
 scalar_t__ LUA_TNUMBER ; 

const TValue* luaR_findentryN(ROTable *rotable, luaR_numkey numkey, unsigned *ppos) {
  unsigned i = 0;
  const luaR_entry *pentry = rotable;
  if (pentry) {
    for ( ;pentry->key.type != LUA_TNIL; i++, pentry++) {
      if (pentry->key.type == LUA_TNUMBER && (luaR_numkey) pentry->key.id.numkey == numkey) {
        if (ppos)
          *ppos = i;
        return &pentry->value;
      }
    }
  }
  return NULL;
}