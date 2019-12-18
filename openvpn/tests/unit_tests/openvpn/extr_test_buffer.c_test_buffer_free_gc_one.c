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
struct gc_arena {scalar_t__ list; } ;
struct buffer {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 struct buffer alloc_buf_gc (int,struct gc_arena*) ; 
 int /*<<< orphan*/  assert_null (scalar_t__) ; 
 int /*<<< orphan*/  assert_ptr_equal (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_buf_gc (struct buffer*,struct gc_arena*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 

__attribute__((used)) static void
test_buffer_free_gc_one(void **state)
{
    struct gc_arena gc = gc_new();
    struct buffer buf = alloc_buf_gc(1024, &gc);

    assert_ptr_equal(gc.list + 1, buf.data);
    free_buf_gc(&buf, &gc);
    assert_null(gc.list);

    gc_free(&gc);
}