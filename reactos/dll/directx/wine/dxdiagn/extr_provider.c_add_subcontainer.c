#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nSubContainers; int /*<<< orphan*/  entry; int /*<<< orphan*/  subContainers; } ;
typedef  TYPE_1__ IDxDiagContainerImpl_Container ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void add_subcontainer(IDxDiagContainerImpl_Container *node, IDxDiagContainerImpl_Container *subCont)
{
    list_add_tail(&node->subContainers, &subCont->entry);
    ++node->nSubContainers;
}