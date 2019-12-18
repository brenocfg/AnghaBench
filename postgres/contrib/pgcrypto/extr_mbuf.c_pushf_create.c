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
struct TYPE_9__ {int block_size; scalar_t__ pos; int /*<<< orphan*/ * buf; struct TYPE_9__* next; void* priv; TYPE_1__ const* op; } ;
struct TYPE_8__ {int (* init ) (TYPE_2__*,void*,void**) ;} ;
typedef  TYPE_1__ PushFilterOps ;
typedef  TYPE_2__ PushFilter ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 void* px_alloc (int) ; 
 int stub1 (TYPE_2__*,void*,void**) ; 

int
pushf_create(PushFilter **mp_p, const PushFilterOps *op, void *init_arg, PushFilter *next)
{
	PushFilter *mp;
	void	   *priv;
	int			res;

	if (op->init != NULL)
	{
		res = op->init(next, init_arg, &priv);
		if (res < 0)
			return res;
	}
	else
	{
		priv = init_arg;
		res = 0;
	}

	mp = px_alloc(sizeof(*mp));
	memset(mp, 0, sizeof(*mp));
	mp->block_size = res;
	mp->op = op;
	mp->priv = priv;
	mp->next = next;
	if (mp->block_size > 0)
	{
		mp->buf = px_alloc(mp->block_size);
		mp->pos = 0;
	}
	else
	{
		mp->buf = NULL;
		mp->pos = 0;
	}
	*mp_p = mp;
	return 0;
}