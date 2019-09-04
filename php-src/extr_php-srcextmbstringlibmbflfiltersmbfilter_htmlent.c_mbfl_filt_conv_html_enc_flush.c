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
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* flush_function ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/ * opaque; scalar_t__ status; } ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

int mbfl_filt_conv_html_enc_flush(mbfl_convert_filter *filter)
{
	filter->status = 0;
	filter->opaque = NULL;

	if (filter->flush_function != NULL) {
		(*filter->flush_function)(filter->data);
	}

	return 0;
}