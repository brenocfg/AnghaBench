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
struct target {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  target__has_cpu (struct target*) ; 
 int /*<<< orphan*/  target__has_task (struct target*) ; 

__attribute__((used)) static inline bool target__none(struct target *target)
{
	return !target__has_task(target) && !target__has_cpu(target);
}