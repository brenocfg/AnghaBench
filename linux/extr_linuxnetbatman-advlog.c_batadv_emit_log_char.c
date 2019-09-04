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
 scalar_t__ batadv_log_buff_len ; 
 char* batadv_log_char_addr (struct batadv_priv_debug_log*,scalar_t__) ; 

__attribute__((used)) static void batadv_emit_log_char(struct batadv_priv_debug_log *debug_log,
				 char c)
{
	char *char_addr;

	char_addr = batadv_log_char_addr(debug_log, debug_log->log_end);
	*char_addr = c;
	debug_log->log_end++;

	if (debug_log->log_end - debug_log->log_start > batadv_log_buff_len)
		debug_log->log_start = debug_log->log_end - batadv_log_buff_len;
}