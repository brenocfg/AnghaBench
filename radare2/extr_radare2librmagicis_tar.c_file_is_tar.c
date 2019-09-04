#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ RMagic ;

/* Variables and functions */
 int R_MAGIC_MIME ; 
 int R_MAGIC_MIME_ENCODING ; 
 int file_printf (TYPE_1__*,char*) ; 
 int is_tar (int /*<<< orphan*/  const*,size_t) ; 
 char** tartype ; 

int file_is_tar(RMagic *ms, const ut8 *buf, size_t nbytes) {
	/*
	 * Do the tar test first, because if the first file in the tar
	 * archive starts with a dot, we can confuse it with an nroff file.
	 */
	int tar = is_tar(buf, nbytes);
	int mime = ms->flags & R_MAGIC_MIME;

	if (tar < 1 || tar > 3) {
		return 0;
	}
	if (mime == R_MAGIC_MIME_ENCODING) {
		return 0;
	}
	if (file_printf (ms, mime ? "application/x-tar" : tartype[tar - 1]) == -1) {
		return -1;
	}
	return 1;
}