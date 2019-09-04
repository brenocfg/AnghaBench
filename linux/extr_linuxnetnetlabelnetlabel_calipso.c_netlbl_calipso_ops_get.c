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
struct netlbl_calipso_ops {int dummy; } ;

/* Variables and functions */
 struct netlbl_calipso_ops const* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calipso_ops ; 

__attribute__((used)) static const struct netlbl_calipso_ops *netlbl_calipso_ops_get(void)
{
	return READ_ONCE(calipso_ops);
}