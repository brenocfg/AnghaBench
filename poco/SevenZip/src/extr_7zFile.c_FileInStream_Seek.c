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
struct TYPE_2__ {int /*<<< orphan*/  file; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  Int64 ;
typedef  int /*<<< orphan*/  ESzSeek ;
typedef  TYPE_1__ CFileInStream ;

/* Variables and functions */
 int /*<<< orphan*/  File_Seek (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SRes FileInStream_Seek(void *pp, Int64 *pos, ESzSeek origin)
{
  CFileInStream *p = (CFileInStream *)pp;
  return File_Seek(&p->file, pos, origin);
}