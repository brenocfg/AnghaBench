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
typedef  int /*<<< orphan*/  signal_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  signal_handler_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool signal_handler_add_array(signal_handler_t *handler,
					    const char **signal_decls)
{
	bool success = true;
	if (!signal_decls)
		return false;

	while (*signal_decls)
		if (!signal_handler_add(handler, *(signal_decls++)))
			success = false;

	return success;
}