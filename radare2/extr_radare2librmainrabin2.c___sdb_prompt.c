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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sdb_query (int /*<<< orphan*/ *,char*) ; 
 char* stdin_gets () ; 

__attribute__((used)) static void __sdb_prompt(Sdb *sdb) {
	char *line;
	for (; (line = stdin_gets ());) {
		sdb_query (sdb, line);
		free (line);
	}
}