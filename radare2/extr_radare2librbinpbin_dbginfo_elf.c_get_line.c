#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_3__ {scalar_t__ sdb_addrinfo; } ;
typedef  TYPE_1__ RBinFile ;

/* Variables and functions */
 int atoi (char*) ; 
 char* sdb_get (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 char* sdb_itoa (int /*<<< orphan*/ ,char*,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int get_line(RBinFile *bf, ut64 addr, char *file, int len, int *line) {
	if (bf->sdb_addrinfo) {
		char offset[64];
		char *offset_ptr = sdb_itoa (addr, offset, 16);
		char *ret = sdb_get (bf->sdb_addrinfo, offset_ptr, 0);
		if (ret) {
			char *p = strchr (ret, '|');
			if (p) {
				*p = '\0';
				strncpy (file, ret, len);
				*line = atoi (p + 1);
				return true;
			}
		}
	}
	return false;
}