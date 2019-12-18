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
typedef  int /*<<< orphan*/  clusterKeyVal ;
struct TYPE_3__ {int size; scalar_t__ len; void* entry; } ;
typedef  TYPE_1__ clusterDistList ;

/* Variables and functions */
 int CLUSTER_KEYDIST_ALLOC ; 
 void* emalloc (int) ; 

__attribute__((used)) static clusterDistList *cluster_dl_create() {
    clusterDistList *dl;

    dl        = emalloc(sizeof(clusterDistList));
    dl->entry = emalloc(CLUSTER_KEYDIST_ALLOC * sizeof(clusterKeyVal));
    dl->size  = CLUSTER_KEYDIST_ALLOC;
    dl->len   = 0;

    return dl;
}