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
struct TYPE_6__ {int /*<<< orphan*/ * opaque; } ;
typedef  TYPE_1__ mbfl_convert_filter ;
struct TYPE_7__ {int /*<<< orphan*/  (* filter_dtor ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_filt_conv_common_dtor (TYPE_1__*) ; 
 int /*<<< orphan*/  mbfl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 TYPE_2__ vtbl_tl_jisx0201_jisx0208 ; 

__attribute__((used)) static void
mbfl_filt_conv_wchar_cp50220_dtor(mbfl_convert_filter *filt)
{
	vtbl_tl_jisx0201_jisx0208.filter_dtor(filt);

	if (filt->opaque != NULL) {
		mbfl_free(filt->opaque);
	}

	mbfl_filt_conv_common_dtor(filt);
}