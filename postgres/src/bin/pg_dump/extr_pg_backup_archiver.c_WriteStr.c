#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* WriteBufPtr ) (TYPE_1__*,char const*,int) ;} ;
typedef  TYPE_1__ ArchiveHandle ;

/* Variables and functions */
 size_t WriteInt (TYPE_1__*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char const*,int) ; 

size_t
WriteStr(ArchiveHandle *AH, const char *c)
{
	size_t		res;

	if (c)
	{
		int			len = strlen(c);

		res = WriteInt(AH, len);
		AH->WriteBufPtr(AH, c, len);
		res += len;
	}
	else
		res = WriteInt(AH, -1);

	return res;
}