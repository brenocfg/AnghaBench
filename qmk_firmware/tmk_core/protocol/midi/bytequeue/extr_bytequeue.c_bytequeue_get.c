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
struct TYPE_3__ {size_t start; size_t length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ byteQueue_t ;
typedef  size_t byteQueueIndex_t ;

/* Variables and functions */

uint8_t bytequeue_get(byteQueue_t* queue, byteQueueIndex_t index) { return queue->data[(queue->start + index) % queue->length]; }