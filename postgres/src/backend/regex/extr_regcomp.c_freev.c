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
struct vars {scalar_t__ subs; scalar_t__ sub10; int err; int /*<<< orphan*/  nlacons; int /*<<< orphan*/ * lacons; int /*<<< orphan*/ * cv2; int /*<<< orphan*/ * cv; int /*<<< orphan*/ * treechain; int /*<<< orphan*/ * tree; int /*<<< orphan*/ * nfa; int /*<<< orphan*/ * re; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (int) ; 
 int /*<<< orphan*/  FREE (scalar_t__) ; 
 int /*<<< orphan*/  cleanst (struct vars*) ; 
 int /*<<< orphan*/  freecvec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freelacons (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freenfa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freesubre (struct vars*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
freev(struct vars *v,
	  int err)
{
	if (v->re != NULL)
		rfree(v->re);
	if (v->subs != v->sub10)
		FREE(v->subs);
	if (v->nfa != NULL)
		freenfa(v->nfa);
	if (v->tree != NULL)
		freesubre(v, v->tree);
	if (v->treechain != NULL)
		cleanst(v);
	if (v->cv != NULL)
		freecvec(v->cv);
	if (v->cv2 != NULL)
		freecvec(v->cv2);
	if (v->lacons != NULL)
		freelacons(v->lacons, v->nlacons);
	ERR(err);					/* nop if err==0 */

	return v->err;
}