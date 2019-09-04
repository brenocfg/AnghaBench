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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  Sdb ;

/* Variables and functions */
 int /*<<< orphan*/  sdb_add (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 char* sdb_itoa (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdb_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_meta_add_fileline(Sdb *s, char *fileline, ut64 offset) {
	char aoffset[64];
	char *aoffsetptr = sdb_itoa (offset, aoffset, 16);

	if (!aoffsetptr) {
		return -1;
	}
	if (!sdb_add (s, aoffsetptr, fileline, 0)) {
		sdb_set (s, aoffsetptr, fileline, 0);
	}
	if (!sdb_add (s, fileline, aoffsetptr, 0)) {
		sdb_set (s, fileline, aoffsetptr, 0);
	}
	return 0;
}