#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* buffer; } ;
typedef  TYPE_2__ xmlreaderinput ;
struct TYPE_7__ {int written; int* data; } ;
typedef  TYPE_3__ encoded_buffer ;
struct TYPE_5__ {TYPE_3__ encoded; } ;

/* Variables and functions */

__attribute__((used)) static int readerinput_get_utf8_convlen(xmlreaderinput *readerinput)
{
    encoded_buffer *buffer = &readerinput->buffer->encoded;
    int len = buffer->written;

    /* complete single byte char */
    if (!(buffer->data[len-1] & 0x80)) return len;

    /* find start byte of multibyte char */
    while (--len && !(buffer->data[len] & 0xc0))
        ;

    return len;
}