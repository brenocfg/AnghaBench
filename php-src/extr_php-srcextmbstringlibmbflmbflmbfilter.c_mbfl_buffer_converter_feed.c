#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mbfl_string ;
typedef  int /*<<< orphan*/  mbfl_buffer_converter ;

/* Variables and functions */
 int mbfl_buffer_converter_feed2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
mbfl_buffer_converter_feed(mbfl_buffer_converter *convd, mbfl_string *string)
{
	return mbfl_buffer_converter_feed2(convd, string, NULL);
}