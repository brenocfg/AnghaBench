#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gdImagePtr ;
struct TYPE_6__ {int /*<<< orphan*/  (* gd_free ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ gdIOCtx ;

/* Variables and functions */
 int /*<<< orphan*/  _gdImageGd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* gdDPExtractData (TYPE_1__*,int*) ; 
 TYPE_1__* gdNewDynamicCtx (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void *gdImageGdPtr (gdImagePtr im, int *size)
{
	void *rv;
	gdIOCtx *out = gdNewDynamicCtx(2048, NULL);
	_gdImageGd(im, out);
	rv = gdDPExtractData(out, size);
	out->gd_free(out);
	return rv;
}