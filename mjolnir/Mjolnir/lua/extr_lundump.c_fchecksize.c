#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ LoadState ;

/* Variables and functions */
 size_t LoadByte (TYPE_1__*) ; 
 int /*<<< orphan*/  error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaO_pushfstring (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void fchecksize (LoadState *S, size_t size, const char *tname) {
  if (LoadByte(S) != size)
    error(S, luaO_pushfstring(S->L, "%s size mismatch in", tname));
}