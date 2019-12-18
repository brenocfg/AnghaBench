#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tomoyo_policy_namespace {int dummy; } ;
struct TYPE_2__ {struct tomoyo_policy_namespace* ns; } ;

/* Variables and functions */
 TYPE_1__* tomoyo_domain () ; 

__attribute__((used)) static inline struct tomoyo_policy_namespace *tomoyo_current_namespace(void)
{
	return tomoyo_domain()->ns;
}