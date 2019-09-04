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
struct batadv_priv_debug_log {scalar_t__ log_end; scalar_t__ log_start; } ;

/* Variables and functions */

__attribute__((used)) static bool batadv_log_empty(struct batadv_priv_debug_log *debug_log)
{
	return !(debug_log->log_start - debug_log->log_end);
}