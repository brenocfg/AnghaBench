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
struct TYPE_3__ {int capacity; int length; int /*<<< orphan*/ * dies; } ;
typedef  int /*<<< orphan*/  RBinDwarfDIE ;
typedef  TYPE_1__ RBinDwarfCompUnit ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int r_bin_dwarf_expand_cu(RBinDwarfCompUnit *cu) {
	RBinDwarfDIE *tmp;

	if (!cu || cu->capacity == 0 || cu->capacity != cu->length) {
		return -EINVAL;
	}

	tmp = (RBinDwarfDIE*)realloc(cu->dies,
			cu->capacity * 2 * sizeof(RBinDwarfDIE));
	if (!tmp) {
		return -ENOMEM;
	}

	memset ((ut8*)tmp + cu->capacity * sizeof (RBinDwarfDIE),
			0, cu->capacity * sizeof (RBinDwarfDIE));
	cu->dies = tmp;
	cu->capacity *= 2;

	return 0;
}