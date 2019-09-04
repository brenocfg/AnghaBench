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
typedef  int /*<<< orphan*/  REgg ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * r_buf_new () ; 
 char* r_egg_option_get (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static RBuffer *build (REgg *egg) {
	RBuffer *buf = r_buf_new ();
	char *key = r_egg_option_get (egg, "key");
	char *seed = r_egg_option_get (egg, "seed");
	eprintf ("TODO: shoorisu yagana shellcode encoder\n");
	free (key);
	free (seed);
	return buf;
}