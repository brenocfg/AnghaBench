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
 scalar_t__ format_is_alpha (int /*<<< orphan*/ ) ; 
 scalar_t__ format_is_number (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL format_is_literal(WCHAR x)
{
    return (format_is_alpha(x) || format_is_number(x));
}