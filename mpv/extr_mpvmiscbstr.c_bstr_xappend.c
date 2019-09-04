#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int len; char* start; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  resize_append (void*,TYPE_1__*,int) ; 

void bstr_xappend(void *talloc_ctx, bstr *s, bstr append)
{
    if (!append.len)
        return;
    resize_append(talloc_ctx, s, append.len + 1);
    memcpy(s->start + s->len, append.start, append.len);
    s->len += append.len;
    s->start[s->len] = '\0';
}