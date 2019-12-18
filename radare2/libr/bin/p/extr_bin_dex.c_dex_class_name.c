#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  class_id; } ;
typedef  int /*<<< orphan*/  RBinDexObj ;
typedef  TYPE_1__ RBinDexClass ;

/* Variables and functions */
 char* dex_class_name_byid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str_cpy (char*,char*) ; 
 scalar_t__ simplifiedDemangling ; 
 int /*<<< orphan*/  simplify (char*) ; 

__attribute__((used)) static char *dex_class_name(RBinDexObj *bin, RBinDexClass *c) {
	char *s = dex_class_name_byid (bin, c->class_id);
	if (simplifiedDemangling) {
		simplify (s);
		if (*s == 'L') {
			r_str_cpy (s, s + 1);
		}
	}
	return s;
}