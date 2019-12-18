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
struct TYPE_3__ {int /*<<< orphan*/ * Key; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__* PINFCACHELINE ;
typedef  int /*<<< orphan*/  PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/ * FrLdrTempAlloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_INF_KEY ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
PVOID
InfpAddKeyToLine(
    PINFCACHELINE Line,
    PCHAR Key)
{
    if (Line == NULL)
        return NULL;

    if (Line->Key != NULL)
        return NULL;

    Line->Key = FrLdrTempAlloc(strlen(Key) + 1, TAG_INF_KEY);
    if (Line->Key == NULL)
        return NULL;

    strcpy(Line->Key, Key);

    return (PVOID)Line->Key;
}