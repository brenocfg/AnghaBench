#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zic_t ;
struct TYPE_4__ {int dontmerge; int type; int /*<<< orphan*/  at; } ;

/* Variables and functions */
 TYPE_1__* attypes ; 
 TYPE_1__* growalloc (TYPE_1__*,int,size_t,int /*<<< orphan*/ *) ; 
 size_t timecnt ; 
 int /*<<< orphan*/  timecnt_alloc ; 

__attribute__((used)) static void
addtt(zic_t starttime, int type)
{
	attypes = growalloc(attypes, sizeof *attypes, timecnt, &timecnt_alloc);
	attypes[timecnt].at = starttime;
	attypes[timecnt].dontmerge = false;
	attypes[timecnt].type = type;
	++timecnt;
}