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
struct vars {scalar_t__* now; int cflags; } ;
typedef  scalar_t__ chr ;

/* Variables and functions */
 scalar_t__ ATEOS () ; 
 scalar_t__ CHR (char) ; 
 int NEXT1 (char) ; 
 int /*<<< orphan*/  NOTE (int /*<<< orphan*/ ) ; 
 int REG_EXPANDED ; 
 int /*<<< orphan*/  REG_UNONPOSIX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ iscspace (scalar_t__) ; 

__attribute__((used)) static void
skip(struct vars *v)
{
	const chr  *start = v->now;

	assert(v->cflags & REG_EXPANDED);

	for (;;)
	{
		while (!ATEOS() && iscspace(*v->now))
			v->now++;
		if (ATEOS() || *v->now != CHR('#'))
			break;				/* NOTE BREAK OUT */
		assert(NEXT1('#'));
		while (!ATEOS() && *v->now != CHR('\n'))
			v->now++;
		/* leave the newline to be picked up by the iscspace loop */
	}

	if (v->now != start)
		NOTE(REG_UNONPOSIX);
}