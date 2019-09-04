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
struct TYPE_2__ {unsigned int uiLast; scalar_t__ pvElements; } ;
typedef  int /*<<< orphan*/  SocketFifoElement_t ;
typedef  TYPE_1__ FIFO_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const* const,int) ; 

__attribute__((used)) static void socketfifo_Push (void * const pvFifo, const void * const pvElement) {
    if ((pvFifo != NULL) && (NULL != pvElement)) {
        unsigned int uiLast = ((FIFO_t *)pvFifo)->uiLast;
        memcpy (&((SocketFifoElement_t *)((FIFO_t *)pvFifo)->pvElements)[uiLast], pvElement, sizeof(SocketFifoElement_t));
    }
}