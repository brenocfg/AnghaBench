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
typedef  int int32 ;
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  HV ;

/* Variables and functions */
 int /*<<< orphan*/  PG_UTF8 ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/ ** hv_fetch (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* pg_server_to_any (char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static SV **
hv_fetch_string(HV *hv, const char *key)
{
	dTHX;
	int32		hlen;
	char	   *hkey;
	SV		  **ret;

	hkey = pg_server_to_any(key, strlen(key), PG_UTF8);

	/* See notes in hv_store_string */
	hlen = -(int) strlen(hkey);
	ret = hv_fetch(hv, hkey, hlen, 0);

	if (hkey != key)
		pfree(hkey);

	return ret;
}