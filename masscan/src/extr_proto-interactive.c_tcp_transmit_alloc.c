#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct InteractiveData {int dummy; } ;

/* Variables and functions */
 unsigned char* MALLOC (size_t) ; 
 int /*<<< orphan*/  UNUSEDPARM (struct InteractiveData*) ; 

unsigned char *
tcp_transmit_alloc(struct InteractiveData *more, size_t length)
{
    /* Note using this parameter yet, but in the future, we are going to have
     * memory pools instead of heap malloc(), which will use this parameter */
    UNUSEDPARM(more);

    return MALLOC(length);
}