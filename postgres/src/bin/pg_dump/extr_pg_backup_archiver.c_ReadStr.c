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
struct TYPE_5__ {int /*<<< orphan*/  (* ReadBufPtr ) (TYPE_1__*,void*,int) ;} ;
typedef  TYPE_1__ ArchiveHandle ;

/* Variables and functions */
 int ReadInt (TYPE_1__*) ; 
 scalar_t__ pg_malloc (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*,int) ; 

char *
ReadStr(ArchiveHandle *AH)
{
	char	   *buf;
	int			l;

	l = ReadInt(AH);
	if (l < 0)
		buf = NULL;
	else
	{
		buf = (char *) pg_malloc(l + 1);
		AH->ReadBufPtr(AH, (void *) buf, l);

		buf[l] = '\0';
	}

	return buf;
}