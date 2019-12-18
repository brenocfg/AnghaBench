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
struct TYPE_3__ {int capacity; int length; int /*<<< orphan*/ * specs; } ;
typedef  int /*<<< orphan*/  RBinDwarfAttrSpec ;
typedef  TYPE_1__ RBinDwarfAbbrevDecl ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int r_bin_dwarf_expand_abbrev_decl(RBinDwarfAbbrevDecl *ad) {
	RBinDwarfAttrSpec *tmp;

	if (!ad || !ad->capacity || ad->capacity != ad->length) {
		return -EINVAL;
	}

	tmp = (RBinDwarfAttrSpec*)realloc (ad->specs,
			ad->capacity * 2 * sizeof (RBinDwarfAttrSpec));

	if (!tmp) {
		return -ENOMEM;
	}

	// Set the area in the buffer past the length to 0
	memset ((ut8*)tmp + ad->capacity * sizeof (RBinDwarfAttrSpec),
			0, ad->capacity * sizeof (RBinDwarfAttrSpec));
	ad->specs = tmp;
	ad->capacity *= 2;

	return 0;
}