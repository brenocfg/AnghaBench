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
struct TYPE_3__ {int len; int size; int /*<<< orphan*/ ** buf; } ;
typedef  TYPE_1__ elem_vector_t ;
typedef  int /*<<< orphan*/  HTMLElement ;

/* Variables and functions */
 int /*<<< orphan*/ ** heap_realloc (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static void elem_vector_add(elem_vector_t *buf, HTMLElement *elem)
{
    if(buf->len == buf->size) {
        buf->size <<= 1;
        buf->buf = heap_realloc(buf->buf, buf->size*sizeof(HTMLElement*));
    }

    buf->buf[buf->len++] = elem;
}