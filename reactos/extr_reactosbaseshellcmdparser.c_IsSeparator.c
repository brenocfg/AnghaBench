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
typedef  scalar_t__ TCHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  STANDARD_SEPS ; 
 scalar_t__ _istspace (scalar_t__) ; 
 scalar_t__ _tcschr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static BOOL IsSeparator(TCHAR Char)
{
    return _istspace(Char) || (Char && _tcschr(STANDARD_SEPS, Char));
}