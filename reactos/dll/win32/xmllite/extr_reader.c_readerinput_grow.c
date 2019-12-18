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
struct TYPE_8__ {int allocated; int written; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ encoded_buffer ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {TYPE_3__ utf16; } ;

/* Variables and functions */
 int max (int,int) ; 
 int /*<<< orphan*/  readerinput_realloc (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void readerinput_grow(xmlreaderinput *readerinput, int length)
{
    encoded_buffer *buffer = &readerinput->buffer->utf16;

    length *= sizeof(WCHAR);
    /* grow if needed, plus 4 bytes to be sure null terminator will fit in */
    if (buffer->allocated < buffer->written + length + 4)
    {
        int grown_size = max(2*buffer->allocated, buffer->allocated + length);
        buffer->data = readerinput_realloc(readerinput, buffer->data, grown_size);
        buffer->allocated = grown_size;
    }
}