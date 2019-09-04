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
typedef  int /*<<< orphan*/  ut32 ;
typedef  int /*<<< orphan*/  Sdb ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* sdb_encode (void const*,int) ; 
 int /*<<< orphan*/  sdb_set (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdb_set_enc(Sdb *db, const char *key, const char *v, ut32 cas) {
	char *estr = sdb_encode ((const void *) v, -1);
	sdb_set (db, key, estr, cas);
	free (estr);
}