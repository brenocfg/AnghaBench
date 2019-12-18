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
typedef  int /*<<< orphan*/  Rangstr ;

/* Variables and functions */
 int /*<<< orphan*/  json_get (char*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rangstr_print (int /*<<< orphan*/ *) ; 

int test_main () {
	Rangstr rs ;

	rs = json_get ("{\"hello\":\"world\"}", "hello");
printf ("OUT: ");
rangstr_print (&rs);
printf ("\n");

printf ("--\n");
	rs = json_get ("{\"hello\":{\"world\":123}}", "hello.world");
printf ("OUT: ");
rangstr_print (&rs);
printf ("\n");
	return 0;
}