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
typedef  int /*<<< orphan*/  pg_wchar ;

/* Variables and functions */
 int pg_euc2wchar_with_len (unsigned char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
pg_euckr2wchar_with_len(const unsigned char *from, pg_wchar *to, int len)
{
	return pg_euc2wchar_with_len(from, to, len);
}