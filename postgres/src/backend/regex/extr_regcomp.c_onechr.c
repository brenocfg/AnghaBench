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
struct vars {int cflags; } ;
struct state {int dummy; } ;
typedef  int /*<<< orphan*/  color ;
typedef  int /*<<< orphan*/  chr ;

/* Variables and functions */
 int /*<<< orphan*/  COLORLESS ; 
 int REG_ICASE ; 
 int /*<<< orphan*/  allcases (struct vars*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subcolorcvec (struct vars*,int /*<<< orphan*/ ,struct state*,struct state*) ; 
 int /*<<< orphan*/  subcoloronechr (struct vars*,int /*<<< orphan*/ ,struct state*,struct state*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
onechr(struct vars *v,
	   chr c,
	   struct state *lp,
	   struct state *rp)
{
	if (!(v->cflags & REG_ICASE))
	{
		color		lastsubcolor = COLORLESS;

		subcoloronechr(v, c, lp, rp, &lastsubcolor);
		return;
	}

	/* rats, need general case anyway... */
	subcolorcvec(v, allcases(v, c), lp, rp);
}