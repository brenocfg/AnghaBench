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
struct vc_data {scalar_t__ vc_num; } ;

/* Variables and functions */
 scalar_t__ fg_console ; 

__attribute__((used)) static inline bool con_is_fg(const struct vc_data *vc)
{
	return vc->vc_num == fg_console;
}