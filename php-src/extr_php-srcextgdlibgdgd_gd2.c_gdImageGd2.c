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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _gdImageGd2 (int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 TYPE_1__* gdNewFileCtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void gdImageGd2 (gdImagePtr im, FILE * outFile, int cs, int fmt)
{
	gdIOCtx *out = gdNewFileCtx(outFile);

	_gdImageGd2(im, out, cs, fmt);

	out->gd_free(out);
}