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
struct TYPE_4__ {scalar_t__ eof; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int stream_read_partial (TYPE_1__*,char*,int) ; 

int stream_read(stream_t *s, char *mem, int total)
{
    int len = total;
    while (len > 0) {
        int read = stream_read_partial(s, mem, len);
        if (read <= 0)
            break; // EOF
        mem += read;
        len -= read;
    }
    total -= len;
    if (total > 0)
        s->eof = 0;
    return total;
}