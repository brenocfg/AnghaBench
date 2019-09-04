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
typedef  scalar_t__ u32 ;
struct iwl_priv {int dummy; } ;

/* Variables and functions */
 int iwl_print_event_log (struct iwl_priv*,scalar_t__,scalar_t__,scalar_t__,int,char**,size_t) ; 

__attribute__((used)) static int iwl_print_last_event_logs(struct iwl_priv *priv, u32 capacity,
				    u32 num_wraps, u32 next_entry,
				    u32 size, u32 mode,
				    int pos, char **buf, size_t bufsz)
{
	/*
	 * display the newest DEFAULT_LOG_ENTRIES entries
	 * i.e the entries just before the next ont that uCode would fill.
	 */
	if (num_wraps) {
		if (next_entry < size) {
			pos = iwl_print_event_log(priv,
						capacity - (size - next_entry),
						size - next_entry, mode,
						pos, buf, bufsz);
			pos = iwl_print_event_log(priv, 0,
						  next_entry, mode,
						  pos, buf, bufsz);
		} else
			pos = iwl_print_event_log(priv, next_entry - size,
						  size, mode, pos, buf, bufsz);
	} else {
		if (next_entry < size) {
			pos = iwl_print_event_log(priv, 0, next_entry,
						  mode, pos, buf, bufsz);
		} else {
			pos = iwl_print_event_log(priv, next_entry - size,
						  size, mode, pos, buf, bufsz);
		}
	}
	return pos;
}