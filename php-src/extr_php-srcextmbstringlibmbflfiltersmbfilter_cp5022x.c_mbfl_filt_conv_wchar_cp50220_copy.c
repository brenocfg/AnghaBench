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
struct TYPE_6__ {int /*<<< orphan*/  last; } ;
typedef  TYPE_1__ mbfl_filt_conv_wchar_cp50220_ctx ;
struct TYPE_7__ {int /*<<< orphan*/ * data; TYPE_1__* opaque; } ;
typedef  TYPE_2__ mbfl_convert_filter ;

/* Variables and functions */
 TYPE_1__* mbfl_malloc (int) ; 

__attribute__((used)) static void
mbfl_filt_conv_wchar_cp50220_copy(mbfl_convert_filter *src, mbfl_convert_filter *dest)
{
	mbfl_filt_conv_wchar_cp50220_ctx *ctx;

	*dest = *src;
	ctx = mbfl_malloc(sizeof(mbfl_filt_conv_wchar_cp50220_ctx));
	if (ctx != NULL) {
		*ctx = *(mbfl_filt_conv_wchar_cp50220_ctx*)src->opaque;
	}

	dest->opaque = ctx;
	dest->data = &ctx->last;
}