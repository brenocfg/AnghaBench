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
struct TYPE_3__ {int /*<<< orphan*/  data; scalar_t__ freedata; } ;
typedef  TYPE_1__ SocketFifoElement_t ;

/* Variables and functions */
 scalar_t__ SOCKETFIFO_Pop (TYPE_1__*) ; 
 int /*<<< orphan*/  mem_Free (int /*<<< orphan*/ ) ; 

void SOCKETFIFO_Flush (void) {
    SocketFifoElement_t element;
    while (SOCKETFIFO_Pop(&element)) {
        if (element.freedata) {
            mem_Free(element.data);
        }
    }
}