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
typedef  int /*<<< orphan*/  bson_t ;

/* Variables and functions */
 int /*<<< orphan*/  bson_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 

void free_bson(bson_t **insert, size_t n_documents) {
    size_t i;

    for(i = 0; i < n_documents; i++)
        bson_destroy(insert[i]);

    free(insert);
}