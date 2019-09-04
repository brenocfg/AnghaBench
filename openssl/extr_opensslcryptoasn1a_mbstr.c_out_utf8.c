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
 scalar_t__ UTF8_putc (int /*<<< orphan*/ *,int,unsigned long) ; 

__attribute__((used)) static int out_utf8(unsigned long value, void *arg)
{
    int *outlen;
    outlen = arg;
    *outlen += UTF8_putc(NULL, -1, value);
    return 1;
}