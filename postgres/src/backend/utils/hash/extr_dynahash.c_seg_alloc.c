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
struct TYPE_3__ {int ssize; scalar_t__ (* alloc ) (int) ;int /*<<< orphan*/  hcxt; } ;
typedef  TYPE_1__ HTAB ;
typedef  int /*<<< orphan*/ * HASHSEGMENT ;
typedef  int /*<<< orphan*/  HASHBUCKET ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentDynaHashCxt ; 
 int /*<<< orphan*/  MemSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int) ; 

__attribute__((used)) static HASHSEGMENT
seg_alloc(HTAB *hashp)
{
	HASHSEGMENT segp;

	CurrentDynaHashCxt = hashp->hcxt;
	segp = (HASHSEGMENT) hashp->alloc(sizeof(HASHBUCKET) * hashp->ssize);

	if (!segp)
		return NULL;

	MemSet(segp, 0, sizeof(HASHBUCKET) * hashp->ssize);

	return segp;
}