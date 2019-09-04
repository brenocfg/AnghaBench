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
struct hlist_head {int dummy; } ;
struct flex_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (struct hlist_head*) ; 
 struct flex_array* flex_array_alloc (int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flex_array_free (struct flex_array*) ; 
 scalar_t__ flex_array_get (struct flex_array*,int) ; 
 int flex_array_prealloc (struct flex_array*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct flex_array *alloc_buckets(unsigned int n_buckets)
{
	struct flex_array *buckets;
	int i, err;

	buckets = flex_array_alloc(sizeof(struct hlist_head),
				   n_buckets, GFP_KERNEL);
	if (!buckets)
		return NULL;

	err = flex_array_prealloc(buckets, 0, n_buckets, GFP_KERNEL);
	if (err) {
		flex_array_free(buckets);
		return NULL;
	}

	for (i = 0; i < n_buckets; i++)
		INIT_HLIST_HEAD((struct hlist_head *)
					flex_array_get(buckets, i));

	return buckets;
}