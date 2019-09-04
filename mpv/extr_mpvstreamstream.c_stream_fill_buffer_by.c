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
struct TYPE_4__ {int sector_size; int buf_len; scalar_t__ buf_pos; int /*<<< orphan*/  buffer; int /*<<< orphan*/  read_chunk; } ;
typedef  TYPE_1__ stream_t ;
typedef  int int64_t ;

/* Variables and functions */
 int MPMAX (int,int /*<<< orphan*/ ) ; 
 int MPMIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STREAM_BUFFER_SIZE ; 
 int stream_read_unbuffered (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stream_fill_buffer_by(stream_t *s, int64_t len)
{
    len = MPMIN(len, s->read_chunk);
    len = MPMAX(len, STREAM_BUFFER_SIZE);
    if (s->sector_size)
        len = s->sector_size;
    len = stream_read_unbuffered(s, s->buffer, len);
    s->buf_pos = 0;
    s->buf_len = len;
    return s->buf_len;
}