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
struct TYPE_5__ {scalar_t__ expires; scalar_t__ date; scalar_t__ options; int /*<<< orphan*/  contenttype; } ;
typedef  TYPE_1__ BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  CT_TEXT_PLAIN ; 
 int /*<<< orphan*/  buffer_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  buffer_overflow_check (TYPE_1__*) ; 

void buffer_reset(BUFFER *wb)
{
    buffer_flush(wb);

    wb->contenttype = CT_TEXT_PLAIN;
    wb->options = 0;
    wb->date = 0;
    wb->expires = 0;

    buffer_overflow_check(wb);
}