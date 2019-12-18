#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_9__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_8__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_7__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_11__ {int /*<<< orphan*/  FileAttributes; TYPE_4__ ChangeTime; TYPE_3__ LastWriteTime; TYPE_2__ LastAccessTime; TYPE_1__ CreationTime; } ;
typedef  TYPE_5__* PFILE_BASIC_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  DbgP (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void print_basic_info(int on, PFILE_BASIC_INFORMATION info)
{
    if (!on) return;
    DbgP("BASIC_INFO: Create=%lx Access=%lx Write=%lx Change=%lx Attr=%x\n",
        info->CreationTime.QuadPart, info->LastAccessTime.QuadPart,
        info->LastWriteTime.QuadPart, info->ChangeTime.QuadPart, 
        info->FileAttributes);
}