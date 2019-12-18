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
typedef  int /*<<< orphan*/  RRegex ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int r_regex_check (int /*<<< orphan*/ *,char*) ; 
 int r_regex_exec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_regex_free (int /*<<< orphan*/ *) ; 
 int r_regex_match (char*,char*,char*) ; 
 int /*<<< orphan*/ * r_regex_new (char*,char*) ; 

__attribute__((used)) static void test_or() {
	RRegex *rx = r_regex_new ("(eax|ebx)", "e");
	printf ("result (%s) = %d\n", "mov eax", r_regex_match("(eax|ebx)", "e", "mov eax"));
	printf ("result (%s) = %d\n", "mov ebx", r_regex_match("(eax|ebx)", "e", "mov ebx"));
	printf ("result (%s) = %d\n", "mov eax", r_regex_match("(eax|ebx)", "e", "mov ecx"));
	printf ("result (%s) = %d\n", "mov ebx", r_regex_match("(eax|ecx)", "e", "mov ebx"));
	printf ("result (%s) = %d\n", "mov eax", r_regex_check(rx, "mov eax"));
	printf ("result (%s) = %d\n", "mov ebx", r_regex_check(rx, "mov ebx"));
	printf ("result (%s) = %d\n", "mov eax", r_regex_exec(rx, "mov eax", 0, 0, 1));
	printf ("result (%s) = %d\n", "mov ebx", r_regex_exec(rx, "mov ebx", 0, 0, 1));
	r_regex_free (rx);
}