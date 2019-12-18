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
typedef  int /*<<< orphan*/  pending_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  is_down (int /*<<< orphan*/ *) ; 

bool is_up(pending_key_t *k) {
    return !is_down(k);
}