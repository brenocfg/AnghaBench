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
struct qdio_irq {int /*<<< orphan*/ * dsci; } ;
struct TYPE_2__ {int /*<<< orphan*/  ind; } ;

/* Variables and functions */
 size_t TIQDIO_SHARED_IND ; 
 TYPE_1__* q_indicators ; 

__attribute__((used)) static inline int references_shared_dsci(struct qdio_irq *irq_ptr)
{
	return irq_ptr->dsci == &q_indicators[TIQDIO_SHARED_IND].ind;
}