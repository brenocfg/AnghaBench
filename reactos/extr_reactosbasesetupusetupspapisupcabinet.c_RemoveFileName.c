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
typedef  int /*<<< orphan*/  VOID ;
typedef  int* PWCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int* GetFileName (int*) ; 

__attribute__((used)) static VOID
RemoveFileName(PWCHAR Path)
{
    PWCHAR FileName;
    DWORD i;

    i = 0;
    FileName = GetFileName(Path + i);

    if (FileName != Path + i && FileName[-1] == L'\\')
        FileName--;

    if (FileName == Path + i && FileName[0] == L'\\')
        FileName++;

    FileName[0] = 0;
}