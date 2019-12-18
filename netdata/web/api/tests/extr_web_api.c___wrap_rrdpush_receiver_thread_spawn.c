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
struct web_client {int dummy; } ;
typedef  int /*<<< orphan*/  RRDHOST ;

/* Variables and functions */

int __wrap_rrdpush_receiver_thread_spawn(RRDHOST *host, struct web_client *w, char *url)
{
    return 0;
}