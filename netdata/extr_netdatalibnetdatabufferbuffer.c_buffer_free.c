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
struct TYPE_5__ {struct TYPE_5__* buffer; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  D_WEB_BUFFER ; 
 int /*<<< orphan*/  buffer_overflow_check (TYPE_1__*) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freez (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

void buffer_free(BUFFER *b) {
    if(unlikely(!b)) return;

    buffer_overflow_check(b);

    debug(D_WEB_BUFFER, "Freeing web buffer of size %zu.", b->size);

    freez(b->buffer);
    freez(b);
}