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
struct TYPE_3__ {int /*<<< orphan*/  rotate_db; } ;
typedef  TYPE_1__ RPanels ;

/* Variables and functions */
 int /*<<< orphan*/  rotateDisasCb ; 
 int /*<<< orphan*/  rotateEntropyHCb ; 
 int /*<<< orphan*/  rotateEntropyVCb ; 
 int /*<<< orphan*/  rotateFunctionCb ; 
 int /*<<< orphan*/  rotateHexdumpCb ; 
 int /*<<< orphan*/  rotateRegisterCb ; 
 int /*<<< orphan*/  sdb_ptr_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void initRotatedb(RPanels *panels) {
	sdb_ptr_set (panels->rotate_db, "pd", &rotateDisasCb, 0);
	sdb_ptr_set (panels->rotate_db, "p==", &rotateEntropyHCb, 0);
	sdb_ptr_set (panels->rotate_db, "p=", &rotateEntropyVCb, 0);
	sdb_ptr_set (panels->rotate_db, "px", &rotateHexdumpCb, 0);
	sdb_ptr_set (panels->rotate_db, "dr", &rotateRegisterCb, 0);
	sdb_ptr_set (panels->rotate_db, "af", &rotateFunctionCb, 0);
}