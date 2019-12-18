#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int buflen; struct TYPE_7__* buf; int /*<<< orphan*/  priv; TYPE_1__* op; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ PullFilter ;

/* Variables and functions */
 int /*<<< orphan*/  px_free (TYPE_2__*) ; 
 int /*<<< orphan*/  px_memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
pullf_free(PullFilter *pf)
{
	if (pf->op->free)
		pf->op->free(pf->priv);

	if (pf->buf)
	{
		px_memset(pf->buf, 0, pf->buflen);
		px_free(pf->buf);
	}

	px_memset(pf, 0, sizeof(*pf));
	px_free(pf);
}