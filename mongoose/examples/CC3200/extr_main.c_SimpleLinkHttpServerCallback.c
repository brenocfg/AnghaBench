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
typedef  int /*<<< orphan*/  SlHttpServerResponse_t ;
typedef  int /*<<< orphan*/  SlHttpServerEvent_t ;

/* Variables and functions */

void SimpleLinkHttpServerCallback(SlHttpServerEvent_t *e,
                                  SlHttpServerResponse_t *resp) {
}