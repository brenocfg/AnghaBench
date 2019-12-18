#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* o; } ;
struct TYPE_4__ {scalar_t__ methods_ht; } ;
typedef  int /*<<< orphan*/  RBinSymbol ;
typedef  TYPE_2__ RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/ * ht_pp_find (scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* sdb_fmt (char*,char const*,char const*) ; 

__attribute__((used)) static RBinSymbol *__getMethod(RBinFile *bf, const char *klass, const char *method) {
	r_return_val_if_fail (bf && bf->o && bf->o->methods_ht && klass && method, NULL);
	const char *name = sdb_fmt ("%s::%s", klass, method);
	return ht_pp_find (bf->o->methods_ht, name, NULL);
}