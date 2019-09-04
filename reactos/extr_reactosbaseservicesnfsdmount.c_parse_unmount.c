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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  root_ref; } ;
typedef  TYPE_1__ nfs41_upcall ;

/* Variables and functions */
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  dprintf (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_unmount(unsigned char *buffer, uint32_t length, nfs41_upcall *upcall) 
{
    dprintf(1, "parsing NFS41_UNMOUNT: root=%p\n", upcall->root_ref);
    return ERROR_SUCCESS;
}