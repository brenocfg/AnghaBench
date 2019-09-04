#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PFATX_DIRENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  CreateDate ; 
 int /*<<< orphan*/  CreateTime ; 
 int /*<<< orphan*/  Date ; 
 int /*<<< orphan*/  LastAccessDate ; 
 int /*<<< orphan*/  LastAccessTime ; 
 int /*<<< orphan*/  SD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Size ; 
 int /*<<< orphan*/  StartCluster ; 
 int /*<<< orphan*/  Time ; 

VOID FatSwapFatXDirEntry(PFATX_DIRENTRY Obj)
{
    SD(Obj, StartCluster);
    SD(Obj, Size);
    SW(Obj, Time);
    SW(Obj, Date);
    SW(Obj, CreateTime);
    SW(Obj, CreateDate);
    SW(Obj, LastAccessTime);
    SW(Obj, LastAccessDate);
}