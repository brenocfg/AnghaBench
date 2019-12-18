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
typedef  int /*<<< orphan*/  text ;

/* Variables and functions */
 int /*<<< orphan*/  GetDatabaseEncoding () ; 
 int /*<<< orphan*/  PG_UTF8 ; 
 int /*<<< orphan*/ * convert_charset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static text *
convert_to_utf8(text *src)
{
	return convert_charset(src, GetDatabaseEncoding(), PG_UTF8);
}