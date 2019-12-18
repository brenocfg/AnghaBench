#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mime_header_encoder_data {TYPE_1__* conv1_filter; } ;
struct TYPE_2__ {int (* filter_function ) (int,TYPE_1__*) ;} ;

/* Variables and functions */
 int stub1 (int,TYPE_1__*) ; 

int
mime_header_encoder_feed(int c, struct mime_header_encoder_data *pe)
{
	return (*pe->conv1_filter->filter_function)(c, pe->conv1_filter);
}