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
typedef  int /*<<< orphan*/ * PSTR ;
typedef  int /*<<< orphan*/ * PCSTR ;

/* Variables and functions */
 int /*<<< orphan*/ * FrLdrHeapAlloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_STRING ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PCSTR CopyString(PCSTR Source)
{
    PSTR Dest;

    if (!Source)
        return NULL;

    Dest = FrLdrHeapAlloc(strlen(Source) + 1, TAG_STRING);
    if (Dest)
        strcpy(Dest, Source);

    return Dest;
}