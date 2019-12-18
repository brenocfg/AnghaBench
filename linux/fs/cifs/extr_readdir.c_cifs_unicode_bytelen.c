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
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cifs_unicode_bytelen(const char *str)
{
	int len;
	const __le16 *ustr = (const __le16 *)str;

	for (len = 0; len <= PATH_MAX; len++) {
		if (ustr[len] == 0)
			return len << 1;
	}
	cifs_dbg(FYI, "Unicode string longer than PATH_MAX found\n");
	return len << 1;
}