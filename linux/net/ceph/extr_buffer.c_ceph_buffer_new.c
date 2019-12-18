#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t iov_len; int /*<<< orphan*/  iov_base; } ;
struct ceph_buffer {size_t alloc_len; TYPE_1__ vec; int /*<<< orphan*/  kref; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_kvmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_buffer*) ; 
 int /*<<< orphan*/  kfree (struct ceph_buffer*) ; 
 struct ceph_buffer* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

struct ceph_buffer *ceph_buffer_new(size_t len, gfp_t gfp)
{
	struct ceph_buffer *b;

	b = kmalloc(sizeof(*b), gfp);
	if (!b)
		return NULL;

	b->vec.iov_base = ceph_kvmalloc(len, gfp);
	if (!b->vec.iov_base) {
		kfree(b);
		return NULL;
	}

	kref_init(&b->kref);
	b->alloc_len = len;
	b->vec.iov_len = len;
	dout("buffer_new %p\n", b);
	return b;
}