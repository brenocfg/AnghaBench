#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gdIOCtxPtr ;
struct TYPE_3__ {scalar_t__ width; scalar_t__ height; scalar_t__ numplanes; scalar_t__ depth; scalar_t__ enctype; scalar_t__ size; scalar_t__ hres; scalar_t__ vres; scalar_t__ numcolors; scalar_t__ mincolors; int topdown; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ bmp_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMP_PALETTE_4 ; 
 int /*<<< orphan*/  gdGetIntLSB (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdGetWordLSB (scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bmp_read_windows_v3_info(gdIOCtxPtr infile, bmp_info_t *info)
{
	if (
	    !gdGetIntLSB(&info->width, infile) ||
	    !gdGetIntLSB(&info->height, infile) ||
	    !gdGetWordLSB(&info->numplanes, infile) ||
	    !gdGetWordLSB(&info->depth, infile) ||
	    !gdGetIntLSB(&info->enctype, infile) ||
	    !gdGetIntLSB(&info->size, infile) ||
	    !gdGetIntLSB(&info->hres, infile) ||
	    !gdGetIntLSB(&info->vres, infile) ||
	    !gdGetIntLSB(&info->numcolors, infile) ||
	    !gdGetIntLSB(&info->mincolors, infile)
	) {
		return 1;
	}

	if (info->height < 0) {
		info->topdown = 1;
		info->height = -info->height;
	} else {
		info->topdown = 0;
	}

	info->type = BMP_PALETTE_4;

	if (info->width <= 0 || info->height <= 0 || info->numplanes <= 0 ||
	        info->depth <= 0  || info->numcolors < 0 || info->mincolors < 0) {
		return 1;
	}

	return 0;
}