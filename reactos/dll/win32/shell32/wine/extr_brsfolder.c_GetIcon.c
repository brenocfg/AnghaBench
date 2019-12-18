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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int iIcon; } ;
typedef  TYPE_1__ SHFILEINFOW ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ LPCITEMIDLIST ;

/* Variables and functions */
 int /*<<< orphan*/  SHGetFileInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int GetIcon(LPCITEMIDLIST lpi, UINT uFlags)
{
    SHFILEINFOW sfi;
    SHGetFileInfoW((LPCWSTR)lpi, 0 ,&sfi, sizeof(SHFILEINFOW), uFlags);
    return sfi.iIcon;
}