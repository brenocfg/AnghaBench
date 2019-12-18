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
struct TYPE_3__ {unsigned int size; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ strbuf_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  unsigned int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * heap_alloc (unsigned int) ; 
 int /*<<< orphan*/ * heap_realloc (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static BOOL strbuf_ensure_size(strbuf_t *buf, unsigned len)
{
    WCHAR *new_buf;
    DWORD new_size;

    if(len <= buf->size)
        return TRUE;

    new_size = buf->size ? buf->size<<1 : 16;
    if(new_size < len)
        new_size = len;
    if(buf->buf)
        new_buf = heap_realloc(buf->buf, new_size*sizeof(WCHAR));
    else
        new_buf = heap_alloc(new_size*sizeof(WCHAR));
    if(!new_buf)
        return FALSE;

    buf->buf = new_buf;
    buf->size = new_size;
    return TRUE;
}