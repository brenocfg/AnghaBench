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
struct TYPE_2__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  function; } ;
typedef  int /*<<< orphan*/  RelcacheCallbackFunction ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL ; 
 size_t MAX_RELCACHE_CALLBACKS ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 size_t relcache_callback_count ; 
 TYPE_1__* relcache_callback_list ; 

void
CacheRegisterRelcacheCallback(RelcacheCallbackFunction func,
							  Datum arg)
{
	if (relcache_callback_count >= MAX_RELCACHE_CALLBACKS)
		elog(FATAL, "out of relcache_callback_list slots");

	relcache_callback_list[relcache_callback_count].function = func;
	relcache_callback_list[relcache_callback_count].arg = arg;

	++relcache_callback_count;
}