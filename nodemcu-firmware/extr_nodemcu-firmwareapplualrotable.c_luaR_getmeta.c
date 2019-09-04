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
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  ROTable ;

/* Variables and functions */
 int /*<<< orphan*/ * luaR_findentry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* rvalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisrotable (int /*<<< orphan*/  const*) ; 

void* luaR_getmeta(ROTable *rotable) {
  const TValue *res = luaR_findentry(rotable, NULL, NULL);
  return res && ttisrotable(res) ? rvalue(res) : NULL;
}