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
typedef  unsigned int uint16_t ;
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 unsigned int stream_read_char (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint16_t stream_read_word_endian(stream_t *s, bool big_endian)
{
    unsigned int y = stream_read_char(s);
    y = (y << 8) | stream_read_char(s);
    if (!big_endian)
        y = ((y >> 8) & 0xFF) | (y << 8);
    return y;
}