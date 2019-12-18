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
typedef  int /*<<< orphan*/  RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rrdpush_sender_thread_custom_host_variables_callback ; 
 int rrdvar_callback_for_all_host_variables (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rrdpush_sender_thread_send_custom_host_variables(RRDHOST *host) {
    int ret = rrdvar_callback_for_all_host_variables(host, rrdpush_sender_thread_custom_host_variables_callback, host);
    (void)ret;

    debug(D_STREAM, "RRDVAR sent %d VARIABLES", ret);
}