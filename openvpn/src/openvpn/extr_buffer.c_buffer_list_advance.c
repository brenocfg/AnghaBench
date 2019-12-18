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
struct buffer_list {TYPE_1__* head; } ;
struct buffer {int dummy; } ;
struct TYPE_2__ {struct buffer buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BLEN (struct buffer*) ; 
 int /*<<< orphan*/  buf_advance (struct buffer*,int) ; 
 int /*<<< orphan*/  buffer_list_pop (struct buffer_list*) ; 

void
buffer_list_advance(struct buffer_list *ol, int n)
{
    if (ol->head)
    {
        struct buffer *buf = &ol->head->buf;
        ASSERT(buf_advance(buf, n));
        if (!BLEN(buf))
        {
            buffer_list_pop(ol);
        }
    }
}