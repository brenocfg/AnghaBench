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
struct buffer_list {int dummy; } ;
struct TYPE_2__ {size_t len; } ;
struct buffer_entry {TYPE_1__ buf; } ;

/* Variables and functions */
 struct buffer_entry* buffer_list_push_data (struct buffer_list*,char const*,size_t const) ; 
 size_t strlen (char const*) ; 

void
buffer_list_push(struct buffer_list *ol, const char *str)
{
    if (str)
    {
        const size_t len = strlen((const char *)str);
        struct buffer_entry *e = buffer_list_push_data(ol, str, len+1);
        if (e)
        {
            e->buf.len = len; /* Don't count trailing '\0' as part of length */
        }
    }
}