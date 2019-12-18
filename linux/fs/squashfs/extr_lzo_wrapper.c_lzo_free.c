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
struct squashfs_lzo {int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct squashfs_lzo*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lzo_free(void *strm)
{
	struct squashfs_lzo *stream = strm;

	if (stream) {
		vfree(stream->input);
		vfree(stream->output);
	}
	kfree(stream);
}