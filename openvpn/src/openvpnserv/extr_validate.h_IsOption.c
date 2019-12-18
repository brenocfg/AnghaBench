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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ wcsncmp (int /*<<< orphan*/  const*,char*,int) ; 

__attribute__((used)) static inline BOOL
IsOption(const WCHAR *o)
{
    return (wcsncmp(o, L"--", 2) == 0);
}