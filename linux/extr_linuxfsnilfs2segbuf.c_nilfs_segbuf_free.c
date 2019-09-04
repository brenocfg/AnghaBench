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
struct nilfs_segment_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nilfs_segment_buffer*) ; 
 int /*<<< orphan*/  nilfs_segbuf_cachep ; 

void nilfs_segbuf_free(struct nilfs_segment_buffer *segbuf)
{
	kmem_cache_free(nilfs_segbuf_cachep, segbuf);
}