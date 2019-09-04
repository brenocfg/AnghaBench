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
struct TYPE_3__ {unsigned int uiLast; unsigned int uiElementsMax; void (* pfElementPush ) (void* const,void const* const) ;void (* pfElementPop ) (void* const,void* const) ;scalar_t__ uiElementCount; scalar_t__ uiFirst; } ;
typedef  TYPE_1__ FIFO_t ;

/* Variables and functions */

void FIFO_Init (FIFO_t *fifo, unsigned int uiElementsMax,
                void (*pfElmentPush)(void * const pvFifo, const void * const pvElement),
                void (*pfElementPop)(void * const pvFifo, void * const pvElement)) {
    if (fifo) {
        fifo->uiFirst = 0;
        fifo->uiLast = uiElementsMax - 1;
        fifo->uiElementCount = 0;
        fifo->uiElementsMax = uiElementsMax;
        fifo->pfElementPush = pfElmentPush;
        fifo->pfElementPop = pfElementPop;
    }
}