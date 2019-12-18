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

/* Variables and functions */
 char* getargpos (char const*,int) ; 
 size_t strtoul (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t getvalue (const char *buf, int pos) {
	size_t ret;
	buf = getargpos (buf, pos);
	if (buf) {
		ret = strtoul (buf, 0, 0);
	} else {
		ret = -1;
	}
	return ret;
}