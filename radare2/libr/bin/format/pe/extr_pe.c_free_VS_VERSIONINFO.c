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
struct TYPE_4__ {int /*<<< orphan*/  stringFileInfo; int /*<<< orphan*/  varFileInfo; struct TYPE_4__* Value; struct TYPE_4__* szKey; } ;
typedef  TYPE_1__ PE_VS_VERSIONINFO ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_StringFileInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_VarFileInfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_VS_VERSIONINFO(PE_VS_VERSIONINFO* vs_VersionInfo) {
	if (vs_VersionInfo) {
		free (vs_VersionInfo->szKey);
		free (vs_VersionInfo->Value);
		free_VarFileInfo (vs_VersionInfo->varFileInfo);
		free_StringFileInfo (vs_VersionInfo->stringFileInfo);
		free (vs_VersionInfo);
	}
}