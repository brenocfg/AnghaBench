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
struct TYPE_3__ {scalar_t__ hash_name; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ RRDSET ;

/* Variables and functions */
 TYPE_1__* rrdset_from_avlname (void*) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rrdset_compare_name(void* a, void* b) {
    RRDSET *A = rrdset_from_avlname(a);
    RRDSET *B = rrdset_from_avlname(b);

    // fprintf(stderr, "COMPARING: %s with %s\n", A->name, B->name);

    if(A->hash_name < B->hash_name) return -1;
    else if(A->hash_name > B->hash_name) return 1;
    else return strcmp(A->name, B->name);
}