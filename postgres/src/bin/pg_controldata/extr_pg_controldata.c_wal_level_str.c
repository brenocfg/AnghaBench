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
typedef  int WalLevel ;

/* Variables and functions */
#define  WAL_LEVEL_LOGICAL 130 
#define  WAL_LEVEL_MINIMAL 129 
#define  WAL_LEVEL_REPLICA 128 
 char const* _ (char*) ; 

__attribute__((used)) static const char *
wal_level_str(WalLevel wal_level)
{
	switch (wal_level)
	{
		case WAL_LEVEL_MINIMAL:
			return "minimal";
		case WAL_LEVEL_REPLICA:
			return "replica";
		case WAL_LEVEL_LOGICAL:
			return "logical";
	}
	return _("unrecognized wal_level");
}