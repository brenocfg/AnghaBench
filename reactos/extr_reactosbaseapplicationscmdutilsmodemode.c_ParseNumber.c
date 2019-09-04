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
typedef  int /*<<< orphan*/  PDWORD ;
typedef  int /*<<< orphan*/ * PCWSTR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 scalar_t__ swscanf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static PCWSTR
ParseNumber(PCWSTR argStr, PDWORD Number)
{
    INT value, skip = 0;

    value = swscanf(argStr, L"%lu%n", Number, &skip);
    if (!value) return NULL;
    argStr += skip;
    return argStr;
}