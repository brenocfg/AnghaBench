#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* static_buffer; char* buffer; } ;
struct lwan_strbuf {int flags; scalar_t__ used; TYPE_1__ value; } ;

/* Variables and functions */
 int STATIC ; 

void lwan_strbuf_reset(struct lwan_strbuf *s)
{
    if (s->flags & STATIC) {
        s->value.static_buffer = "";
    } else {
        s->value.buffer[0] = '\0';
    }

    s->used = 0;
}