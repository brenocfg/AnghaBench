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
struct flex_array {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct flex_array* flex_array_alloc (size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flex_array_free (struct flex_array*) ; 
 int flex_array_prealloc (struct flex_array*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct flex_array *fa_alloc(size_t elem_size, size_t elem_count,
				   gfp_t gfp)
{
	struct flex_array *result;
	int err;

	result = flex_array_alloc(elem_size, elem_count, gfp);
	if (result) {
		err = flex_array_prealloc(result, 0, elem_count, gfp);
		if (err) {
			flex_array_free(result);
			result = NULL;
		}
	}

	return result;
}