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
struct TYPE_3__ {scalar_t__ stringFileInfo; scalar_t__ varFileInfo; scalar_t__ Value; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  TYPE_1__ PE_VS_VERSIONINFO ;

/* Variables and functions */
 int /*<<< orphan*/  Pe_r_bin_store_fixed_file_info (scalar_t__) ; 
 int /*<<< orphan*/  Pe_r_bin_store_string_file_info (scalar_t__) ; 
 int /*<<< orphan*/  Pe_r_bin_store_var_file_info (scalar_t__) ; 
 int /*<<< orphan*/ * sdb_new0 () ; 
 int /*<<< orphan*/  sdb_ns_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Sdb* Pe_r_bin_store_resource_version_info(PE_VS_VERSIONINFO* vs_VersionInfo) {
	Sdb* sdb = NULL;
	if (!vs_VersionInfo) {
		return NULL;
	}
	sdb = sdb_new0 ();
	if (!sdb) {
		return NULL;
	}
	if (vs_VersionInfo->Value) {
		sdb_ns_set (sdb, "fixed_file_info", Pe_r_bin_store_fixed_file_info (vs_VersionInfo->Value));
	}
	if (vs_VersionInfo->varFileInfo) {
		sdb_ns_set (sdb, "var_file_info", Pe_r_bin_store_var_file_info (vs_VersionInfo->varFileInfo));
	}
	if (vs_VersionInfo->stringFileInfo) {
		sdb_ns_set (sdb, "string_file_info", Pe_r_bin_store_string_file_info (vs_VersionInfo->stringFileInfo));
	}
	return sdb;
}