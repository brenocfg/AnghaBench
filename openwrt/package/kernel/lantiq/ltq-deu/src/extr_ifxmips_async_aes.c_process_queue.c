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
struct TYPE_2__ {int /*<<< orphan*/  aes_event_flags; int /*<<< orphan*/  deu_thread_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_ASYNC_EVENT ; 
 int /*<<< orphan*/  DEU_WAKEUP_EVENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ deu_dma_priv ; 

__attribute__((used)) static void process_queue(unsigned long data)
{

    DEU_WAKEUP_EVENT(deu_dma_priv.deu_thread_wait, AES_ASYNC_EVENT,
                deu_dma_priv.aes_event_flags);
}