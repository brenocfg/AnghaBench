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
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ iswalpha (char) ; 

__attribute__((used)) static BOOL is_identifier_first_char(WCHAR c)
{
    return iswalpha(c) || c == '$' || c == '_' || c == '\\';
}