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
struct dsos {int dummy; } ;
struct dso {int dummy; } ;

/* Variables and functions */
 struct dso* __dsos__addnew (struct dsos*,char const*) ; 
 struct dso* __dsos__find (struct dsos*,char const*,int) ; 

struct dso *__dsos__findnew(struct dsos *dsos, const char *name)
{
	struct dso *dso = __dsos__find(dsos, name, false);

	return dso ? dso : __dsos__addnew(dsos, name);
}