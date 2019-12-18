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
struct mime_header_decoder_data {int dummy; } ;

/* Variables and functions */
 int mime_header_decoder_collector (int,struct mime_header_decoder_data*) ; 

int
mime_header_decoder_feed(int c, struct mime_header_decoder_data *pd)
{
	return mime_header_decoder_collector(c, pd);
}