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
struct TYPE_2__ {int /*<<< orphan*/  backend_file; int /*<<< orphan*/  backend; int /*<<< orphan*/  backend_size; int /*<<< orphan*/  backend_addr; } ;
struct mic_info {TYPE_1__ mic_virtblk; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
close_backend(struct mic_info *mic)
{
	munmap(mic->mic_virtblk.backend_addr, mic->mic_virtblk.backend_size);
	close(mic->mic_virtblk.backend);
	free(mic->mic_virtblk.backend_file);
}