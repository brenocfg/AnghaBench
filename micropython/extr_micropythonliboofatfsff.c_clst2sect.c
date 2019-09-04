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
struct TYPE_3__ {int n_fatent; int database; int csize; } ;
typedef  TYPE_1__ FATFS ;
typedef  int DWORD ;

/* Variables and functions */

__attribute__((used)) static DWORD clst2sect (    /* !=0:Sector number, 0:Failed (invalid cluster#) */
    FATFS* fs,      /* Filesystem object */
    DWORD clst      /* Cluster# to be converted */
)
{
    clst -= 2;      /* Cluster number is origin from 2 */
    if (clst >= fs->n_fatent - 2) return 0;     /* Is it invalid cluster number? */
    return fs->database + fs->csize * clst;     /* Start sector number of the cluster */
}