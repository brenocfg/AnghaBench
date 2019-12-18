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
typedef  int /*<<< orphan*/  Sdb ;

/* Variables and functions */
 char* sdb_const_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sdb_ns (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static const char* get_compile_time(Sdb *binFileSdb) {
	Sdb *info_ns = sdb_ns (binFileSdb, "info", false);
	const char *timeDateStamp_string = sdb_const_get (info_ns,
		"image_file_header.TimeDateStamp_string", 0);
	return timeDateStamp_string;
}