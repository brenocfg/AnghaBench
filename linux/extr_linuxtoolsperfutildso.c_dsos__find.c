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
struct dsos {int /*<<< orphan*/  lock; } ;
struct dso {int dummy; } ;

/* Variables and functions */
 struct dso* __dsos__find (struct dsos*,char const*,int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct dso *dsos__find(struct dsos *dsos, const char *name, bool cmp_short)
{
	struct dso *dso;
	down_read(&dsos->lock);
	dso = __dsos__find(dsos, name, cmp_short);
	up_read(&dsos->lock);
	return dso;
}