#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
struct TYPE_3__ {scalar_t__ type_info; } ;
typedef  TYPE_1__ STypeInfo ;
typedef  TYPE_2__ SLF_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  free_sval (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_lf_member(void *type_info) {
	STypeInfo *typeInfo = (STypeInfo *) type_info;
	SLF_MEMBER *lf_mem = (SLF_MEMBER *) typeInfo->type_info;
	free_sval (&lf_mem->offset);
}