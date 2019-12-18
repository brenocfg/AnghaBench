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
struct TYPE_4__ {unsigned int LineLength; struct TYPE_4__* ContribRow; struct TYPE_4__* Weights; } ;
typedef  TYPE_1__ LineContribType ;

/* Variables and functions */
 int /*<<< orphan*/  gdFree (TYPE_1__*) ; 

__attribute__((used)) static inline void _gdContributionsFree(LineContribType * p)
{
	unsigned int u;
	for (u = 0; u < p->LineLength; u++)  {
		gdFree(p->ContribRow[u].Weights);
	}
	gdFree(p->ContribRow);
	gdFree(p);
}