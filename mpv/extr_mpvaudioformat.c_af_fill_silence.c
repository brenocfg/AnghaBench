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

/* Variables and functions */
 scalar_t__ af_fmt_is_unsigned (int) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 

void af_fill_silence(void *dst, size_t bytes, int format)
{
    memset(dst, af_fmt_is_unsigned(format) ? 0x80 : 0, bytes);
}