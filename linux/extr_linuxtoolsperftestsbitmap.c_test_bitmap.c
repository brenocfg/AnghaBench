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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  NBITS ; 
 int /*<<< orphan*/  bitmap_scnprintf (unsigned long*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (unsigned long*) ; 
 unsigned long* get_bitmap (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static int test_bitmap(const char *str)
{
	unsigned long *bm = get_bitmap(str, NBITS);
	char buf[100];
	int ret;

	bitmap_scnprintf(bm, NBITS, buf, sizeof(buf));
	pr_debug("bitmap: %s\n", buf);

	ret = !strcmp(buf, str);
	free(bm);
	return ret;
}