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
struct gc_entry {struct gc_entry* next; } ;
struct gc_arena {struct gc_entry* list; } ;
struct buffer {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 struct buffer alloc_buf_gc (int,struct gc_arena*) ; 
 int /*<<< orphan*/  assert_non_null (struct gc_entry*) ; 
 int /*<<< orphan*/  assert_ptr_equal (struct gc_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_ptr_not_equal (struct gc_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_buf_gc (struct buffer*,struct gc_arena*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 

__attribute__((used)) static void
test_buffer_free_gc_two(void **state)
{
    struct gc_arena gc = gc_new();
    struct buffer buf1 = alloc_buf_gc(1024, &gc);
    struct buffer buf2 = alloc_buf_gc(1024, &gc);
    struct buffer buf3 = alloc_buf_gc(1024, &gc);

    struct gc_entry *e;

    e = gc.list;

    assert_ptr_equal(e + 1, buf3.data);
    assert_ptr_equal(e->next + 1, buf2.data);
    assert_ptr_equal(e->next->next + 1, buf1.data);

    free_buf_gc(&buf2, &gc);

    assert_non_null(gc.list);

    while (e)
    {
        assert_ptr_not_equal(e + 1, buf2.data);
        e = e->next;
    }

    gc_free(&gc);
}