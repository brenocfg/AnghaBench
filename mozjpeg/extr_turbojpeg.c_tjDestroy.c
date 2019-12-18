#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tjhandle ;
struct TYPE_4__ {int /*<<< orphan*/  setjmp_buffer; } ;
struct TYPE_5__ {int init; TYPE_1__ jerr; } ;

/* Variables and functions */
 int COMPRESS ; 
 int DECOMPRESS ; 
 int /*<<< orphan*/  cinfo ; 
 int /*<<< orphan*/  dinfo ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  getinstance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_destroy_compress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_destroy_decompress (int /*<<< orphan*/ ) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 TYPE_2__* this ; 

int tjDestroy(tjhandle handle)
{
	getinstance(handle);

	if(setjmp(this->jerr.setjmp_buffer)) return -1;
	if(this->init&COMPRESS) jpeg_destroy_compress(cinfo);
	if(this->init&DECOMPRESS) jpeg_destroy_decompress(dinfo);
	free(this);
	return 0;
}