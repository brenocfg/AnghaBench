#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* buffer; } ;
typedef  TYPE_2__ xmlreaderinput ;
struct TYPE_8__ {int data; int cur; int written; } ;
typedef  TYPE_3__ encoded_buffer ;
struct TYPE_6__ {TYPE_3__ encoded; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int,int,int) ; 
 int readerinput_get_convlen (TYPE_2__*) ; 

__attribute__((used)) static void readerinput_shrinkraw(xmlreaderinput *readerinput, int len)
{
    encoded_buffer *buffer = &readerinput->buffer->encoded;

    if (len == -1)
        len = readerinput_get_convlen(readerinput);

    memmove(buffer->data, buffer->data + buffer->cur + (buffer->written - len), len);
    /* everything below cur is lost too */
    buffer->written -= len + buffer->cur;
    /* after this point we don't need cur offset really,
       it's used only to mark where actual data begins when first chunk is read */
    buffer->cur = 0;
}