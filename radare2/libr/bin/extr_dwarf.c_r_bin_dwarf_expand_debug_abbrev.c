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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_3__ {int capacity; int length; int /*<<< orphan*/ * decls; } ;
typedef  TYPE_1__ RBinDwarfDebugAbbrev ;
typedef  int /*<<< orphan*/  RBinDwarfAbbrevDecl ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int r_bin_dwarf_expand_debug_abbrev(RBinDwarfDebugAbbrev *da) {
	RBinDwarfAbbrevDecl *tmp;

	if (!da || da->capacity == 0 || da->capacity != da->length) {
		return -EINVAL;
	}

	tmp = (RBinDwarfAbbrevDecl*)realloc (da->decls,
			da->capacity * 2 * sizeof (RBinDwarfAbbrevDecl));

	if (!tmp) {
		return -ENOMEM;
	}
	memset ((ut8*)tmp + da->capacity * sizeof (RBinDwarfAbbrevDecl),
			0, da->capacity * sizeof (RBinDwarfAbbrevDecl));

	da->decls = tmp;
	da->capacity *= 2;

	return 0;
}