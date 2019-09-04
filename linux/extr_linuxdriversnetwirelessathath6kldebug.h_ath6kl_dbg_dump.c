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
typedef  enum ATH6K_DEBUG_MASK { ____Placeholder_ATH6K_DEBUG_MASK } ATH6K_DEBUG_MASK ;

/* Variables and functions */

__attribute__((used)) static inline void ath6kl_dbg_dump(enum ATH6K_DEBUG_MASK mask,
				   const char *msg, const char *prefix,
				   const void *buf, size_t len)
{
}