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
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (void*,char**,int,int /*<<< orphan*/ ) ; 
 char* js_nextiterator (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushiterator (int /*<<< orphan*/ *,int,int) ; 
 char** talloc_new (void*) ; 
 int /*<<< orphan*/  talloc_strdup (void*,char const*) ; 

__attribute__((used)) static int get_obj_properties(void *ta_ctx, char ***keys, js_State *J, int idx)
{
    int length = 0;
    js_pushiterator(J, idx, 1);

    *keys = talloc_new(ta_ctx);
    const char *name;
    while ((name = js_nextiterator(J, -1)))
        MP_TARRAY_APPEND(ta_ctx, *keys, length, talloc_strdup(ta_ctx, name));

    js_pop(J, 1);  // the iterator
    return length;
}