#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int (* output_function ) (int,void*) ;int (* flush_function ) (void*) ;TYPE_2__* opaque; struct TYPE_12__* data; scalar_t__ filter_flush; scalar_t__ filter_function; } ;
struct TYPE_10__ {int mode; } ;
struct TYPE_11__ {TYPE_3__ last; TYPE_1__ tl_param; } ;
typedef  TYPE_2__ mbfl_filt_conv_wchar_cp50220_ctx ;
typedef  TYPE_3__ mbfl_convert_filter ;
struct TYPE_13__ {int /*<<< orphan*/  (* filter_ctor ) (TYPE_3__*) ;scalar_t__ filter_flush; scalar_t__ filter_function; } ;

/* Variables and functions */
 int MBFL_FILT_TL_HAN2ZEN_GLUE ; 
 int MBFL_FILT_TL_HAN2ZEN_KATAKANA ; 
 int /*<<< orphan*/  mbfl_filt_conv_common_ctor (TYPE_3__*) ; 
 int /*<<< orphan*/  mbfl_filt_conv_common_dtor (TYPE_3__*) ; 
 TYPE_2__* mbfl_malloc (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 TYPE_4__ vtbl_tl_jisx0201_jisx0208 ; 

__attribute__((used)) static void
mbfl_filt_conv_wchar_cp50220_ctor(mbfl_convert_filter *filt)
{
	mbfl_filt_conv_wchar_cp50220_ctx *ctx;

	mbfl_filt_conv_common_ctor(filt);

	ctx = mbfl_malloc(sizeof(mbfl_filt_conv_wchar_cp50220_ctx));
	if (ctx == NULL) {
		mbfl_filt_conv_common_dtor(filt);
		return;
	}

	ctx->tl_param.mode = MBFL_FILT_TL_HAN2ZEN_KATAKANA | MBFL_FILT_TL_HAN2ZEN_GLUE;

	ctx->last = *filt;
	ctx->last.opaque = ctx;
	ctx->last.data = filt->data;
	filt->filter_function = vtbl_tl_jisx0201_jisx0208.filter_function;
	filt->filter_flush = vtbl_tl_jisx0201_jisx0208.filter_flush;
	filt->output_function = (int(*)(int, void *))ctx->last.filter_function;
	filt->flush_function = (int(*)(void *))ctx->last.filter_flush;
	filt->data = &ctx->last;
	filt->opaque = ctx;
	vtbl_tl_jisx0201_jisx0208.filter_ctor(filt);
}