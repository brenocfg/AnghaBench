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
struct vars {int /*<<< orphan*/  const* stop; int /*<<< orphan*/  const* now; int /*<<< orphan*/  const* savestop; int /*<<< orphan*/  const* savenow; } ;
typedef  int /*<<< orphan*/  chr ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lexnest(struct vars *v,
		const chr *beginp,		/* start of interpolation */
		const chr *endp)		/* one past end of interpolation */
{
	assert(v->savenow == NULL); /* only one level of nesting */
	v->savenow = v->now;
	v->savestop = v->stop;
	v->now = beginp;
	v->stop = endp;
}