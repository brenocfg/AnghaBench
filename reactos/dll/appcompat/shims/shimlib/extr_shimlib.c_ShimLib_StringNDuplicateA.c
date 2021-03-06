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
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/  PSTR ;
typedef  int /*<<< orphan*/  PCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ShimLib_ShimMalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StringCchCopyA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

PCSTR ShimLib_StringNDuplicateA(PCSTR szString, SIZE_T stringLengthIncludingNullTerm)
{
    PSTR NewString = ShimLib_ShimMalloc(stringLengthIncludingNullTerm);
    StringCchCopyA(NewString, stringLengthIncludingNullTerm, szString);
    return NewString;
}