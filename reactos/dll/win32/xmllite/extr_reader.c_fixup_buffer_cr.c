#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* data; int written; scalar_t__ prev_cr; } ;
typedef  TYPE_1__ encoded_buffer ;
typedef  char WCHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static void fixup_buffer_cr(encoded_buffer *buffer, int off)
{
    BOOL prev_cr = buffer->prev_cr;
    const WCHAR *src;
    WCHAR *dest;

    src = dest = (WCHAR*)buffer->data + off;
    while ((const char*)src < buffer->data + buffer->written)
    {
        if (*src == '\r')
        {
            *dest++ = '\n';
            src++;
            prev_cr = TRUE;
            continue;
        }
        if(prev_cr && *src == '\n')
            src++;
        else
            *dest++ = *src++;
        prev_cr = FALSE;
    }

    buffer->written = (char*)dest - buffer->data;
    buffer->prev_cr = prev_cr;
    *dest = 0;
}