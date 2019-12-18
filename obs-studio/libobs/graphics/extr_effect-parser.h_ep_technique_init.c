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
struct ep_technique {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ep_technique*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ep_technique_init(struct ep_technique *ept)
{
	memset(ept, 0, sizeof(struct ep_technique));
}