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
typedef  size_t UINT ;
struct TYPE_4__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  int /*<<< orphan*/ **** LPWSTR ;

/* Variables and functions */
 size_t ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ****) ; 
 size_t msi_apply_patch_package (TYPE_1__*,int /*<<< orphan*/ ****) ; 
 int /*<<< orphan*/ ****** msi_dup_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ ****) ; 
 int /*<<< orphan*/ ******* msi_split_string (int /*<<< orphan*/ ****,char) ; 
 int /*<<< orphan*/  szPatch ; 

UINT msi_apply_patches( MSIPACKAGE *package )
{
    LPWSTR patch_list, *patches;
    UINT i, r = ERROR_SUCCESS;

    patch_list = msi_dup_property( package->db, szPatch );

    TRACE("patches to be applied: %s\n", debugstr_w(patch_list));

    patches = msi_split_string( patch_list, ';' );
    for (i = 0; patches && patches[i] && r == ERROR_SUCCESS; i++)
        r = msi_apply_patch_package( package, patches[i] );

    msi_free( patches );
    msi_free( patch_list );
    return r;
}