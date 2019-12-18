#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  opaque; } ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 scalar_t__ html_enc_buffer_size ; 
 int /*<<< orphan*/  mbfl_malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void mbfl_filt_conv_html_dec_copy(mbfl_convert_filter *src, mbfl_convert_filter *dest)
{
	*dest = *src;
	dest->opaque = mbfl_malloc(html_enc_buffer_size+1);
	memcpy(dest->opaque, src->opaque, html_enc_buffer_size+1);
}