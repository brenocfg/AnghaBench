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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  readbuf ;
typedef  size_t off_t ;

/* Variables and functions */
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 size_t pread (int,int /*<<< orphan*/ *,size_t,size_t) ; 

uint32_t compute_crc32(uint32_t crc, off_t start, size_t compute_len, int fd)
{
	uint8_t readbuf[1024];
	ssize_t res;
	off_t offset = start;

	/* Read a buffer's worth of bytes  */
	while (fd && (compute_len >= sizeof(readbuf))) {
		res = pread(fd, readbuf, sizeof(readbuf), offset);
		crc = crc32(crc, readbuf, res);
		compute_len = compute_len - res;
		offset += res;
	}

	/* Less than buffer-size bytes remains, read compute_len bytes */
	if (fd && (compute_len > 0)) {
	  res = pread(fd, readbuf, compute_len, offset);
	  crc = crc32(crc, readbuf, res);
	}

	return crc;
}