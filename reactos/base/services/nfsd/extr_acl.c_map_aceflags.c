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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ACE4_DIRECTORY_INHERIT_ACE ; 
 int /*<<< orphan*/  ACE4_FILE_INHERIT_ACE ; 
 int /*<<< orphan*/  ACE4_INHERITED_ACE ; 
 int /*<<< orphan*/  ACE4_INHERIT_ONLY_ACE ; 
 int /*<<< orphan*/  ACE4_NO_PROPAGATE_INHERIT_ACE ; 
 int /*<<< orphan*/  ACLLVL ; 
 int CONTAINER_INHERIT_ACE ; 
 int INHERITED_ACE ; 
 int INHERIT_ONLY_ACE ; 
 int NO_PROPAGATE_INHERIT_ACE ; 
 int OBJECT_INHERIT_ACE ; 
 int /*<<< orphan*/  dprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void map_aceflags(BYTE win_aceflags, uint32_t *nfs4_aceflags)
{
    if (win_aceflags & OBJECT_INHERIT_ACE)
        *nfs4_aceflags |= ACE4_FILE_INHERIT_ACE;
    if (win_aceflags & CONTAINER_INHERIT_ACE)
        *nfs4_aceflags |= ACE4_DIRECTORY_INHERIT_ACE;
    if (win_aceflags & NO_PROPAGATE_INHERIT_ACE)
        *nfs4_aceflags |= ACE4_NO_PROPAGATE_INHERIT_ACE;
    if (win_aceflags & INHERIT_ONLY_ACE)
        *nfs4_aceflags |= ACE4_INHERIT_ONLY_ACE;
    if (win_aceflags & INHERITED_ACE)
        *nfs4_aceflags |= ACE4_INHERITED_ACE;
    dprintf(ACLLVL, "ACE FLAGS: %x nfs4 aceflags %x\n", 
            win_aceflags, *nfs4_aceflags);
}