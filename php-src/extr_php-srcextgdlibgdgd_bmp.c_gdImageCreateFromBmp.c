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
typedef  int /*<<< orphan*/ * gdImagePtr ;
struct TYPE_5__ {int /*<<< orphan*/  (* gd_free ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ gdIOCtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * gdImageCreateFromBmpCtx (TYPE_1__*) ; 
 TYPE_1__* gdNewFileCtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

gdImagePtr gdImageCreateFromBmp(FILE * inFile)
{
	gdImagePtr im = 0;
	gdIOCtx *in = gdNewFileCtx(inFile);
	if (in == NULL) return NULL;
	im = gdImageCreateFromBmpCtx(in);
	in->gd_free(in);
	return im;
}