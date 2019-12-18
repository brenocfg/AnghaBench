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
 int qnxr_send_vcont (int /*<<< orphan*/ *,int,int) ; 

int qnxr_step (libqnxr_t *g, int thread_id) {
	return qnxr_send_vcont (g, 1, thread_id);
}