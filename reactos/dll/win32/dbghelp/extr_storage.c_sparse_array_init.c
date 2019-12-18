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
struct sparse_array {int /*<<< orphan*/  elements; int /*<<< orphan*/  key2index; } ;
struct key2index {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vector_init (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

void sparse_array_init(struct sparse_array* sa, unsigned elt_sz, unsigned bucket_sz)
{
    vector_init(&sa->key2index, sizeof(struct key2index), bucket_sz);
    vector_init(&sa->elements, elt_sz, bucket_sz);
}