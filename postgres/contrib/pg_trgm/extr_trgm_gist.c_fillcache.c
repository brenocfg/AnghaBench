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
struct TYPE_3__ {int allistrue; scalar_t__ sign; } ;
typedef  int /*<<< orphan*/  TRGM ;
typedef  TYPE_1__ CACHESIGN ;
typedef  int /*<<< orphan*/  BITVEC ;

/* Variables and functions */
 scalar_t__ GETSIGN (int /*<<< orphan*/ *) ; 
 scalar_t__ ISALLTRUE (int /*<<< orphan*/ *) ; 
 scalar_t__ ISARRKEY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makesign (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static void
fillcache(CACHESIGN *item, TRGM *key)
{
	item->allistrue = false;
	if (ISARRKEY(key))
		makesign(item->sign, key);
	else if (ISALLTRUE(key))
		item->allistrue = true;
	else
		memcpy((void *) item->sign, (void *) GETSIGN(key), sizeof(BITVEC));
}