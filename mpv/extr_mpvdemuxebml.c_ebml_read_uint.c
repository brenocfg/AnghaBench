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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 int EBML_UINT_INVALID ; 
 int ebml_read_length (int /*<<< orphan*/ *) ; 
 int stream_read_char (int /*<<< orphan*/ *) ; 

uint64_t ebml_read_uint(stream_t *s)
{
    uint64_t len, value = 0;

    len = ebml_read_length(s);
    if (len == EBML_UINT_INVALID || len > 8)
        return EBML_UINT_INVALID;

    while (len--)
        value = (value << 8) | stream_read_char(s);

    return value;
}