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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CP_ACP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IsValidCodePage (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 

__attribute__((used)) static BOOL validate_codepage( UINT codepage )
{
    if (codepage != CP_ACP && !IsValidCodePage( codepage ))
    {
        WARN("invalid codepage %u\n", codepage);
        return FALSE;
    }
    return TRUE;
}