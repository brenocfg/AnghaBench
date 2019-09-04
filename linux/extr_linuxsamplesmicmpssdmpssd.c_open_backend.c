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
struct TYPE_2__ {scalar_t__ backend; scalar_t__ backend_addr; int /*<<< orphan*/  backend_file; int /*<<< orphan*/  backend_size; } ;
struct mic_info {TYPE_1__ mic_virtblk; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,long) ; 
 int /*<<< orphan*/  mpsslog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_backend_file (struct mic_info*) ; 
 int /*<<< orphan*/  set_backend_size (struct mic_info*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
open_backend(struct mic_info *mic)
{
	if (!set_backend_file(mic))
		goto _error_exit;
	mic->mic_virtblk.backend = open(mic->mic_virtblk.backend_file, O_RDWR);
	if (mic->mic_virtblk.backend < 0) {
		mpsslog("%s: can't open: %s\n", mic->name,
			mic->mic_virtblk.backend_file);
		goto _error_free;
	}
	if (!set_backend_size(mic))
		goto _error_close;
	mic->mic_virtblk.backend_addr = mmap(NULL,
		mic->mic_virtblk.backend_size,
		PROT_READ|PROT_WRITE, MAP_SHARED,
		mic->mic_virtblk.backend, 0L);
	if (mic->mic_virtblk.backend_addr == MAP_FAILED) {
		mpsslog("%s: can't map: %s %s\n",
			mic->name, mic->mic_virtblk.backend_file,
			strerror(errno));
		goto _error_close;
	}
	return true;

 _error_close:
	close(mic->mic_virtblk.backend);
 _error_free:
	free(mic->mic_virtblk.backend_file);
 _error_exit:
	return false;
}