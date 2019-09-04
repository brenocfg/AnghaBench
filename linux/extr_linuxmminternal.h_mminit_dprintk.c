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
typedef  enum mminit_level { ____Placeholder_mminit_level } mminit_level ;

/* Variables and functions */

__attribute__((used)) static inline void mminit_dprintk(enum mminit_level level,
				const char *prefix, const char *fmt, ...)
{
}