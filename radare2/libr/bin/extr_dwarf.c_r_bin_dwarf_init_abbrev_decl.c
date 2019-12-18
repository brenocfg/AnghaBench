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
struct TYPE_3__ {scalar_t__ length; int /*<<< orphan*/  capacity; int /*<<< orphan*/  specs; } ;
typedef  int /*<<< orphan*/  RBinDwarfAttrSpec ;
typedef  TYPE_1__ RBinDwarfAbbrevDecl ;

/* Variables and functions */
 int /*<<< orphan*/  ABBREV_DECL_CAP ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  calloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_bin_dwarf_init_abbrev_decl(RBinDwarfAbbrevDecl *ad) {
	if (!ad) {
		return -EINVAL;
	}
	ad->specs = calloc (sizeof( RBinDwarfAttrSpec), ABBREV_DECL_CAP);

	if (!ad->specs) {
		return -ENOMEM;
	}

	ad->capacity = ABBREV_DECL_CAP;
	ad->length = 0;

	return 0;
}