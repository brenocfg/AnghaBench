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
struct squashfs_xz {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct squashfs_xz*) ; 
 int /*<<< orphan*/  xz_dec_end (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void squashfs_xz_free(void *strm)
{
	struct squashfs_xz *stream = strm;

	if (stream) {
		xz_dec_end(stream->state);
		kfree(stream);
	}
}