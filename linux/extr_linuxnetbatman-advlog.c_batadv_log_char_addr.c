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
struct batadv_priv_debug_log {char* log_buff; } ;

/* Variables and functions */
 size_t BATADV_LOG_BUFF_MASK ; 

__attribute__((used)) static char *batadv_log_char_addr(struct batadv_priv_debug_log *debug_log,
				  size_t idx)
{
	return &debug_log->log_buff[idx & BATADV_LOG_BUFF_MASK];
}