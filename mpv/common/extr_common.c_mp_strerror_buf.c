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
 int /*<<< orphan*/  AVERROR (int) ; 
 int /*<<< orphan*/  av_strerror (int /*<<< orphan*/ ,char*,size_t) ; 

char *mp_strerror_buf(char *buf, size_t buf_size, int errnum)
{
    // This handles the nasty details of calling the right function for us.
    av_strerror(AVERROR(errnum), buf, buf_size);
    return buf;
}