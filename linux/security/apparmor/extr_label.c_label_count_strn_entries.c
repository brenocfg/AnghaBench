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
 int /*<<< orphan*/  AA_BUG (int) ; 
 char* aa_label_strn_split (char const*,int) ; 

__attribute__((used)) static int label_count_strn_entries(const char *str, size_t n)
{
	const char *end = str + n;
	const char *split;
	int count = 1;

	AA_BUG(!str);

	for (split = aa_label_strn_split(str, end - str);
	     split;
	     split = aa_label_strn_split(str, end - str)) {
		count++;
		str = split + 3;
	}

	return count;
}