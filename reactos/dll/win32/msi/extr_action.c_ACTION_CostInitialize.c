#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ MSIPACKAGE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  load_all_files (TYPE_1__*) ; 
 int /*<<< orphan*/  load_all_folders (TYPE_1__*) ; 
 int /*<<< orphan*/  load_all_media (TYPE_1__*) ; 
 int /*<<< orphan*/  load_all_patches (TYPE_1__*) ; 
 int /*<<< orphan*/  msi_load_all_components (TYPE_1__*) ; 
 int /*<<< orphan*/  msi_load_all_features (TYPE_1__*) ; 
 int /*<<< orphan*/  msi_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  szCRoot ; 
 int /*<<< orphan*/  szCostingComplete ; 
 int /*<<< orphan*/  szRootDrive ; 
 int /*<<< orphan*/  szZero ; 

__attribute__((used)) static UINT ACTION_CostInitialize(MSIPACKAGE *package)
{
    msi_set_property( package->db, szCostingComplete, szZero, -1 );
    msi_set_property( package->db, szRootDrive, szCRoot, -1 );

    load_all_folders( package );
    msi_load_all_components( package );
    msi_load_all_features( package );
    load_all_files( package );
    load_all_patches( package );
    load_all_media( package );

    return ERROR_SUCCESS;
}