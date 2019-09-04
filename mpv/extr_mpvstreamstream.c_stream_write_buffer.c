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
struct TYPE_4__ {int (* write_buffer ) (TYPE_1__*,unsigned char*,int) ;int pos; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,unsigned char*,int) ; 

int stream_write_buffer(stream_t *s, unsigned char *buf, int len)
{
    int rd;
    if (!s->write_buffer)
        return -1;
    rd = s->write_buffer(s, buf, len);
    if (rd < 0)
        return -1;
    s->pos += rd;
    assert(rd == len && "stream_write_buffer(): unexpected short write");
    return rd;
}