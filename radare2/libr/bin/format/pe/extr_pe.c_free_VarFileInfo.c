#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ut32 ;
struct TYPE_5__ {size_t numOfChildren; struct TYPE_5__* Children; struct TYPE_5__* szKey; } ;
typedef  TYPE_1__ VarFileInfo ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_Var (TYPE_1__) ; 

__attribute__((used)) static void free_VarFileInfo(VarFileInfo* varFileInfo) {
	if (varFileInfo) {
		free (varFileInfo->szKey);
		if (varFileInfo->Children) {
			ut32 children = 0;
			for (; children < varFileInfo->numOfChildren; children++) {
				free_Var (varFileInfo->Children[children]);
			}
			free (varFileInfo->Children);
		}
		free (varFileInfo);
	}
}