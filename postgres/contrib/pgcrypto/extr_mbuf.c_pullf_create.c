#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int buflen; scalar_t__ pos; int /*<<< orphan*/ * buf; struct TYPE_9__* src; void* priv; TYPE_1__ const* op; } ;
struct TYPE_8__ {int (* init ) (void**,void*,TYPE_2__*) ;} ;
typedef  TYPE_1__ PullFilterOps ;
typedef  TYPE_2__ PullFilter ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 void* px_alloc (int) ; 
 int stub1 (void**,void*,TYPE_2__*) ; 

int
pullf_create(PullFilter **pf_p, const PullFilterOps *op, void *init_arg, PullFilter *src)
{
	PullFilter *pf;
	void	   *priv;
	int			res;

	if (op->init != NULL)
	{
		res = op->init(&priv, init_arg, src);
		if (res < 0)
			return res;
	}
	else
	{
		priv = init_arg;
		res = 0;
	}

	pf = px_alloc(sizeof(*pf));
	memset(pf, 0, sizeof(*pf));
	pf->buflen = res;
	pf->op = op;
	pf->priv = priv;
	pf->src = src;
	if (pf->buflen > 0)
	{
		pf->buf = px_alloc(pf->buflen);
		pf->pos = 0;
	}
	else
	{
		pf->buf = NULL;
		pf->pos = 0;
	}
	*pf_p = pf;
	return 0;
}