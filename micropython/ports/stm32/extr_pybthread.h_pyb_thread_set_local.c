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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ local_state; } ;

/* Variables and functions */
 TYPE_1__* pyb_thread_cur ; 

__attribute__((used)) static inline void pyb_thread_set_local(void *value) {
    pyb_thread_cur->local_state = (uint32_t)value;
}