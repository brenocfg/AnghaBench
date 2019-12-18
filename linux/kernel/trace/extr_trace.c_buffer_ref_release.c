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
struct buffer_ref {int /*<<< orphan*/  page; int /*<<< orphan*/  cpu; int /*<<< orphan*/  buffer; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct buffer_ref*) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_buffer_free_read_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void buffer_ref_release(struct buffer_ref *ref)
{
	if (!refcount_dec_and_test(&ref->refcount))
		return;
	ring_buffer_free_read_page(ref->buffer, ref->cpu, ref->page);
	kfree(ref);
}