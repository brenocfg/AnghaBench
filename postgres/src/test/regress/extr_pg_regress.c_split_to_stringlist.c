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
typedef  int /*<<< orphan*/  _stringlist ;

/* Variables and functions */
 int /*<<< orphan*/  add_stringlist_item (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* pg_strdup (char const*) ; 
 char* strtok (char*,char const*) ; 

__attribute__((used)) static void
split_to_stringlist(const char *s, const char *delim, _stringlist **listhead)
{
	char	   *sc = pg_strdup(s);
	char	   *token = strtok(sc, delim);

	while (token)
	{
		add_stringlist_item(listhead, token);
		token = strtok(NULL, delim);
	}
	free(sc);
}