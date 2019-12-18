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
typedef  int /*<<< orphan*/  Table ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  TString ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  gkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gnext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* gval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hashstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* luaO_nilobject ; 
 int /*<<< orphan*/ * rawtsvalue (int /*<<< orphan*/ ) ; 
 scalar_t__ ttisstring (int /*<<< orphan*/ ) ; 

const TValue *luaH_getstr (Table *t, TString *key) {
  Node *n = hashstr(t, key);
  do {  /* check whether `key' is somewhere in the chain */
    if (ttisstring(gkey(n)) && rawtsvalue(gkey(n)) == key)
      return gval(n);  /* that's it */
    else n = gnext(n);
  } while (n);
  return luaO_nilobject;
}