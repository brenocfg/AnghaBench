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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 scalar_t__ stream_read_partial (int /*<<< orphan*/ *,int*,int) ; 

int stream_read_char_fallback(stream_t *s)
{
    uint8_t c;
    return stream_read_partial(s, &c, 1) ? c : -256;
}