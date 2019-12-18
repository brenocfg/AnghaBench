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
struct TYPE_2__ {int /*<<< orphan*/ * planes; } ;
struct buffer {int /*<<< orphan*/  size; TYPE_1__ mpi; int /*<<< orphan*/  pool; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_buffer_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_shm_pool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void buffer_destroy(void *p)
{
    struct buffer *buf = p;
    wl_buffer_destroy(buf->buffer);
    wl_shm_pool_destroy(buf->pool);
    munmap(buf->mpi.planes[0], buf->size);
}