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
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int MAX_METADATA_STRING_LENGTH ; 
 char r_buf_read8_at (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int bin_pe_read_metadata_string(char* to, RBuffer *frombuf, int fromoff) {
	int covered = 0;
	while (covered < MAX_METADATA_STRING_LENGTH) {
		char covch = r_buf_read8_at (frombuf, covered);
		to[covered] = covch;
		if (covch == '\0') {
			covered += 1;
			break;
		}
		covered++;
	}
	while (covered % 4 != 0) { covered++; }
	return covered;
}