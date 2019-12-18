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
struct cvec {int cclasscode; scalar_t__ nranges; scalar_t__ nchrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cvec *
clearcvec(struct cvec *cv)
{
	assert(cv != NULL);
	cv->nchrs = 0;
	cv->nranges = 0;
	cv->cclasscode = -1;
	return cv;
}