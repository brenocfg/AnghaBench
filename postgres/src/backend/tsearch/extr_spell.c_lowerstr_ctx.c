#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  buildCxt; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ IspellDict ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 char* lowerstr (char const*) ; 

__attribute__((used)) static char *
lowerstr_ctx(IspellDict *Conf, const char *src)
{
	MemoryContext saveCtx;
	char	   *dst;

	saveCtx = MemoryContextSwitchTo(Conf->buildCxt);
	dst = lowerstr(src);
	MemoryContextSwitchTo(saveCtx);

	return dst;
}