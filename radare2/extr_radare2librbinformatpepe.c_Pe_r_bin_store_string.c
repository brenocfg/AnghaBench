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
struct TYPE_3__ {int /*<<< orphan*/  wValueLength; scalar_t__ Value; int /*<<< orphan*/  wKeyLen; scalar_t__ szKey; } ;
typedef  TYPE_1__ String ;
typedef  int /*<<< orphan*/  Sdb ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* sdb_encode (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sdb_new0 () ; 
 int /*<<< orphan*/  sdb_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Sdb* Pe_r_bin_store_string(String* string) {
	Sdb* sdb = NULL;
	char* encodedVal = NULL, * encodedKey = NULL;
	if (!string) {
		return NULL;
	}
	sdb = sdb_new0 ();
	if (!sdb) {
		return NULL;
	}
	encodedKey = sdb_encode ((unsigned char*) string->szKey, string->wKeyLen);
	if (!encodedKey) {
		sdb_free (sdb);
		return NULL;
	}
	encodedVal = sdb_encode ((unsigned char*) string->Value, string->wValueLength);
	if (!encodedVal) {
		free (encodedKey);
		sdb_free (sdb);
		return NULL;
	}
	sdb_set (sdb, "key",   encodedKey, 0);
	sdb_set (sdb, "value", encodedVal, 0);
	free (encodedKey);
	free (encodedVal);
	return sdb;
}