#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* old_closer ) (scalar_t__) ;} ;
struct TYPE_6__ {scalar_t__ handle; TYPE_1__ mmap; } ;
typedef  TYPE_2__ zend_stream ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  zend_stream_unmap (TYPE_2__*) ; 

__attribute__((used)) static void zend_stream_mmap_closer(zend_stream *stream) /* {{{ */
{
	zend_stream_unmap(stream);
	if (stream->mmap.old_closer && stream->handle) {
		stream->mmap.old_closer(stream->handle);
	}
}