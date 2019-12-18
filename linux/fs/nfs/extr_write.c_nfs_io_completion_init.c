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
struct nfs_io_completion {void (* complete ) (void*) ;int /*<<< orphan*/  refcount; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_io_completion_init(struct nfs_io_completion *ioc,
		void (*complete)(void *), void *data)
{
	ioc->complete = complete;
	ioc->data = data;
	kref_init(&ioc->refcount);
}