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
struct cvec {scalar_t__ nchrs; scalar_t__ chrspace; int /*<<< orphan*/ * chrs; } ;
typedef  int /*<<< orphan*/  chr ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
addchr(struct cvec *cv,			/* character vector */
	   chr c)					/* character to add */
{
	assert(cv->nchrs < cv->chrspace);
	cv->chrs[cv->nchrs++] = c;
}