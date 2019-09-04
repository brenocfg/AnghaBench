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
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int output_string (int /*<<< orphan*/ ,char const*,char*) ; 

__attribute__((used)) static int output_error( int msg )
{
    static const WCHAR fmtW[] = {'%','s',0};
    WCHAR buffer[8192];

    LoadStringW( GetModuleHandleW(NULL), msg, buffer, ARRAY_SIZE(buffer));
    return output_string( GetStdHandle(STD_ERROR_HANDLE), fmtW, buffer );
}