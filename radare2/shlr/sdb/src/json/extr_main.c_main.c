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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  Rangstr ;

/* Variables and functions */
 char* api_json_set (char*,char*,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  json_get (char*,char*) ; 
 int json_geti (char*,char*) ; 
 char* json_seti (char*,char*,...) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rangstr_print (int /*<<< orphan*/ *) ; 
 char* sdb_json_indent (char*,char*) ; 
 char* sdb_json_unindent (char*) ; 
 int /*<<< orphan*/  stdin ; 

int main(int argc, char **argv) {
	Rangstr rs;
	char buf[4096];
	int n = fread (buf, 1, sizeof (buf), stdin);
	buf[n] = 0;
//return test_glossary (buf);
//return test_main ();
	char *path = argv[1];

#if 1
	printf (">>>> %s <<<<\n", sdb_json_unindent (buf));
	printf (">>>> %s <<<<\n", sdb_json_indent (buf, "  "));
// set value //
	path = "glossary.title";
	char *s = api_json_set (buf, path, "patata");
	if (s) {
		printf ("%s\n", s);
		free (s);
	} else printf ("set failed\n");
#endif
//printf ("%s\n", str); return 0;

//	s = "[1,3,4]";
#if 0
	char *a = "{}";
	a = json_seti (a, "id", 123);
	a = json_seti (a, "user.name", "blah");
	printf ("id = %d\n", json_geti ("{'id':123}", "id"));
#endif
	//json_walk (buf);

	path = argv[1];
	rs = json_get (buf, path);
	printf ("-- output --\n");
	rangstr_print(&rs);
	printf ("\n");
	return 0;
}