#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gdIOCtx {int dummy; } ;
struct TYPE_3__ {TYPE_2__* dp; } ;
typedef  TYPE_1__ dpIOCtx ;
struct TYPE_4__ {scalar_t__ dataGood; } ;

/* Variables and functions */
 int /*<<< orphan*/  appendDynamic (TYPE_2__*,void const*,int) ; 

__attribute__((used)) static int
dynamicPutbuf (struct gdIOCtx *ctx, const void *buf, int size)
{
  dpIOCtx *dctx;
  dctx = (dpIOCtx *) ctx;

  appendDynamic (dctx->dp, buf, size);

  if (dctx->dp->dataGood)
    {
      return size;
    }
  else
    {
      return -1;
    };

}