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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {int NameLength; } ;
typedef  TYPE_1__* PFILENAME_ATTRIBUTE ;

/* Variables and functions */
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILENAME_ATTRIBUTE ; 
 int /*<<< orphan*/  Name ; 

ULONG GetFileNameAttributeLength(PFILENAME_ATTRIBUTE FileNameAttribute)
{
    ULONG Length = FIELD_OFFSET(FILENAME_ATTRIBUTE, Name) + (FileNameAttribute->NameLength * sizeof(WCHAR));
    return Length;
}