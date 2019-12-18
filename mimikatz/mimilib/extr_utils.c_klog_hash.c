#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t USHORT ;
struct TYPE_3__ {size_t Length; scalar_t__ Buffer; } ;
typedef  TYPE_1__* PUNICODE_STRING ;
typedef  int /*<<< orphan*/ * LPCBYTE ;
typedef  int /*<<< orphan*/  FILE ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  klog (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 

void klog_hash(FILE * logfile, PUNICODE_STRING pHash, BOOLEAN withSpace)
{
	USHORT i;
	if(pHash->Buffer)
		for(i = 0; i < pHash->Length; i++)
			klog(logfile, L"%02x%s", ((LPCBYTE) pHash->Buffer)[i], withSpace ? " " : "");
}