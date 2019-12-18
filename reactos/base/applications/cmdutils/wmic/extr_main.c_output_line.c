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
typedef  int /*<<< orphan*/  ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int output_string (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int output_line( const WCHAR *str, ULONG column_width )
{
    static const WCHAR fmtW[] = {'%','-','*','s','\r','\n',0};
    return output_string( GetStdHandle(STD_OUTPUT_HANDLE), fmtW, column_width, str );
}