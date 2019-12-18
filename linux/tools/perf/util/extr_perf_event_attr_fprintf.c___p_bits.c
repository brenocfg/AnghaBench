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
typedef  int u64 ;
struct bit_names {int bit; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  scnprintf (char*,size_t,char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __p_bits(char *buf, size_t size, u64 value, struct bit_names *bits)
{
	bool first_bit = true;
	int i = 0;

	do {
		if (value & bits[i].bit) {
			buf += scnprintf(buf, size, "%s%s", first_bit ? "" : "|", bits[i].name);
			first_bit = false;
		}
	} while (bits[++i].name != NULL);
}