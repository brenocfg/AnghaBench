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
 int /*<<< orphan*/  __dsos__add (struct dsos*,struct dso*) ; 
 struct dso* dso__new (char const*) ; 
 int /*<<< orphan*/  dso__put (struct dso*) ; 
 int /*<<< orphan*/  dso__set_basename (struct dso*) ; 

struct dso *__dsos__addnew(struct dsos *dsos, const char *name)
{
	struct dso *dso = dso__new(name);

	if (dso != NULL) {
		__dsos__add(dsos, dso);
		dso__set_basename(dso);
		/* Put dso here because __dsos_add already got it */
		dso__put(dso);
	}
	return dso;
}