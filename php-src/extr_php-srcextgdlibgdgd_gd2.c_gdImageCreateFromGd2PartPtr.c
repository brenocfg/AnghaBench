#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gdImagePtr ;
struct TYPE_5__ {int /*<<< orphan*/  (* gd_free ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ gdIOCtx ;

/* Variables and functions */
 int /*<<< orphan*/  gdImageCreateFromGd2PartCtx (TYPE_1__*,int,int,int,int) ; 
 TYPE_1__* gdNewDynamicCtxEx (int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

gdImagePtr gdImageCreateFromGd2PartPtr (int size, void *data, int srcx, int srcy, int w, int h)
{
	gdImagePtr im;
	gdIOCtx *in = gdNewDynamicCtxEx(size, data, 0);
	im = gdImageCreateFromGd2PartCtx(in, srcx, srcy, w, h);
	in->gd_free(in);

	return im;
}