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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 int EBML_ID_INVALID ; 
 int stream_read_char (int /*<<< orphan*/ *) ; 

uint32_t ebml_read_id(stream_t *s)
{
    int i, len_mask = 0x80;
    uint32_t id;

    for (i = 0, id = stream_read_char(s); i < 4 && !(id & len_mask); i++)
        len_mask >>= 1;
    if (i >= 4)
        return EBML_ID_INVALID;
    while (i--)
        id = (id << 8) | stream_read_char(s);
    return id;
}