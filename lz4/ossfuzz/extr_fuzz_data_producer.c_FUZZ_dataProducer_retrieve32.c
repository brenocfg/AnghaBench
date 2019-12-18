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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  const uint32_t ;
struct TYPE_3__ {size_t size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ FUZZ_dataProducer_t ;

/* Variables and functions */

uint32_t FUZZ_dataProducer_retrieve32(FUZZ_dataProducer_t *producer) {
    const uint8_t* data = producer->data;
    const size_t size = producer->size;
    if (size == 0) {
        return 0;
    } else if (size < 4) {
        producer->size -= 1;
        return (uint32_t)data[size - 1];
    } else {
        producer->size -= 4;
        return *(data + size - 4);
    }
}