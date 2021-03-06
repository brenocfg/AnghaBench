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
 int /*<<< orphan*/  WriteInt (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  _WriteBuf (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static void
_CustomWriteFunc(ArchiveHandle *AH, const char *buf, size_t len)
{
	/* never write 0-byte blocks (this should not happen) */
	if (len > 0)
	{
		WriteInt(AH, len);
		_WriteBuf(AH, buf, len);
	}
	return;
}