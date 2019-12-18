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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  TarMethodFile ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ PGAlignedXLogBlock ;

/* Variables and functions */
 size_t Min (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOG_BLCKSZ ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tar_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static bool
tar_write_padding_data(TarMethodFile *f, size_t bytes)
{
	PGAlignedXLogBlock zerobuf;
	size_t		bytesleft = bytes;

	memset(zerobuf.data, 0, XLOG_BLCKSZ);
	while (bytesleft)
	{
		size_t		bytestowrite = Min(bytesleft, XLOG_BLCKSZ);
		ssize_t		r = tar_write(f, zerobuf.data, bytestowrite);

		if (r < 0)
			return false;
		bytesleft -= r;
	}

	return true;
}