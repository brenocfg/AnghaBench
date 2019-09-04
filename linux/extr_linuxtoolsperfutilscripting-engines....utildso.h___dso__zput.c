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
struct dso {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dso__put (struct dso*) ; 

__attribute__((used)) static inline void __dso__zput(struct dso **dso)
{
	dso__put(*dso);
	*dso = NULL;
}