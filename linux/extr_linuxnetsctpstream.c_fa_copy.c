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

/* Variables and functions */
 void* flex_array_get (struct flex_array*,size_t) ; 
 int /*<<< orphan*/  flex_array_put (struct flex_array*,size_t,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fa_copy(struct flex_array *fa, struct flex_array *from,
		    size_t index, size_t count)
{
	void *elem;

	while (count--) {
		elem = flex_array_get(from, index);
		flex_array_put(fa, index, elem, 0);
		index++;
	}
}