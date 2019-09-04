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
struct TYPE_2__ {scalar_t__ timeout; } ;

/* Variables and functions */
 scalar_t__ SERVERS_MIN_TIMEOUT_MS ; 
 int /*<<< orphan*/  mp_raise_ValueError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpexception_value_invalid_arguments ; 
 TYPE_1__ servers_data ; 

void servers_set_timeout (uint32_t timeout) {
    if (timeout < SERVERS_MIN_TIMEOUT_MS) {
        // timeout is too low
        mp_raise_ValueError(mpexception_value_invalid_arguments);
    }
    servers_data.timeout = timeout;
}