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
struct TYPE_3__ {int (* output_function ) (int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int stub1 (int,int /*<<< orphan*/ ) ; 

int mbfl_filt_conv_ascii_wchar(int c, mbfl_convert_filter *filter)
{
	return (*filter->output_function)(c, filter->data);
}