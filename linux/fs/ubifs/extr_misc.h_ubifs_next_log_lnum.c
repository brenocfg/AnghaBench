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
struct ubifs_info {int log_last; } ;

/* Variables and functions */
 int UBIFS_LOG_LNUM ; 

__attribute__((used)) static inline int ubifs_next_log_lnum(const struct ubifs_info *c, int lnum)
{
	lnum += 1;
	if (lnum > c->log_last)
		lnum = UBIFS_LOG_LNUM;

	return lnum;
}