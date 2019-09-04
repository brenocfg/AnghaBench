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

/* Variables and functions */
 char* api_json_get (char*,char*) ; 
 char* api_json_set (char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int test_glossary(char *buf) {
	char *path;
{
	path = "glossary.title";
	char *s= api_json_set (buf, path, "patata");
	if (s) {
		printf ("%s\n", s);
		free (s);
	} else printf ("set failed\n");
}
{
	path = "glossary.title";
	char *s= api_json_get (buf, path);
	if (s) {
		printf ("%s\n", s);
		free (s);
	} else printf ("set failed\n");
}
{
	path = "glossary.title";
	char *s= api_json_get (buf, path);
	if (s) {
		printf ("%s\n", s);
		free (s);
	} else printf ("set failed\n");
}
return 0;
}