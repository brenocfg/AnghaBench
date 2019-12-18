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
struct vars {int dummy; } ;
struct cvec {int dummy; } ;
typedef  scalar_t__ chr ;

/* Variables and functions */
 int /*<<< orphan*/  addchr (struct cvec*,scalar_t__) ; 
 struct cvec* getcvec (struct vars*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_wc_tolower (scalar_t__) ; 
 scalar_t__ pg_wc_toupper (scalar_t__) ; 

__attribute__((used)) static struct cvec *
allcases(struct vars *v,		/* context */
		 chr c)					/* character to get case equivs of */
{
	struct cvec *cv;
	chr			lc,
				uc;

	lc = pg_wc_tolower(c);
	uc = pg_wc_toupper(c);

	cv = getcvec(v, 2, 0);
	addchr(cv, lc);
	if (lc != uc)
		addchr(cv, uc);
	return cv;
}