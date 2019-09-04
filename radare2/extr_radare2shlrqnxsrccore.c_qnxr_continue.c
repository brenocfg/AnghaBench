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
typedef  int /*<<< orphan*/  libqnxr_t ;

/* Variables and functions */
 int qnxr_send_vcont (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int qnxr_continue (libqnxr_t *g, int thread_id) {
	return qnxr_send_vcont (g, 0, thread_id);
}