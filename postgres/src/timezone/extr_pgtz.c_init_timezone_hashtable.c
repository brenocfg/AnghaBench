#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pg_tz_cache ;
typedef  int /*<<< orphan*/  hash_ctl ;
struct TYPE_4__ {int entrysize; scalar_t__ keysize; } ;
typedef  TYPE_1__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ELEM ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TZ_STRLEN_MAX ; 
 int /*<<< orphan*/  hash_create (char*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timezone_cache ; 

__attribute__((used)) static bool
init_timezone_hashtable(void)
{
	HASHCTL		hash_ctl;

	MemSet(&hash_ctl, 0, sizeof(hash_ctl));

	hash_ctl.keysize = TZ_STRLEN_MAX + 1;
	hash_ctl.entrysize = sizeof(pg_tz_cache);

	timezone_cache = hash_create("Timezones",
								 4,
								 &hash_ctl,
								 HASH_ELEM);
	if (!timezone_cache)
		return false;

	return true;
}