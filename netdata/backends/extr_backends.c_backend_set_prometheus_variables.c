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
typedef  int /*<<< orphan*/ * backend_response_checker_t ;
typedef  int /*<<< orphan*/  backend_request_formatter_t ;

/* Variables and functions */
 int /*<<< orphan*/  process_prometheus_remote_write_response ; 

void backend_set_prometheus_variables(int *default_port,
                                      backend_response_checker_t brc,
                                      backend_request_formatter_t brf)
{
    (void)default_port;
    (void)brf;
#ifndef ENABLE_PROMETHEUS_REMOTE_WRITE
    (void)brc;
#endif

#if ENABLE_PROMETHEUS_REMOTE_WRITE
    *brc = process_prometheus_remote_write_response;
#endif /* ENABLE_PROMETHEUS_REMOTE_WRITE */
}