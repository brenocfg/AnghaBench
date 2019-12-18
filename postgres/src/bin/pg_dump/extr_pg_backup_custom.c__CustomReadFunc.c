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
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 size_t ReadInt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ReadBuf (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ pg_malloc (size_t) ; 

__attribute__((used)) static size_t
_CustomReadFunc(ArchiveHandle *AH, char **buf, size_t *buflen)
{
	size_t		blkLen;

	/* Read length */
	blkLen = ReadInt(AH);
	if (blkLen == 0)
		return 0;

	/* If the caller's buffer is not large enough, allocate a bigger one */
	if (blkLen > *buflen)
	{
		free(*buf);
		*buf = (char *) pg_malloc(blkLen);
		*buflen = blkLen;
	}

	/* exits app on read errors */
	_ReadBuf(AH, *buf, blkLen);

	return blkLen;
}