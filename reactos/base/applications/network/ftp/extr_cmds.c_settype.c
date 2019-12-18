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
struct types {scalar_t__ t_name; char* t_arg; int /*<<< orphan*/  t_type; int /*<<< orphan*/  t_mode; } ;

/* Variables and functions */
 int COMPLETE ; 
 int code ; 
 int command (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,scalar_t__) ; 
 int /*<<< orphan*/  type ; 
 char* typename ; 
 struct types* types ; 

void settype(int argc, const char *argv[])
{
	register struct types *p;
	int comret;

	if (argc > 2) {
		const char *sep;

		printf("usage: %s [", argv[0]);
		sep = " ";
		for (p = types; p->t_name; p++) {
			printf("%s%s", sep, p->t_name);
			if (*sep == ' ')
				sep = " | ";
		}
		printf(" ]\n");
		(void) fflush(stdout);
		code = -1;
		return;
	}
	if (argc < 2) {
		printf("Using %s mode to transfer files.\n", typename);
		(void) fflush(stdout);
		code = 0;
		return;
	}
	for (p = types; p->t_name; p++)
		if (strcmp(argv[1], p->t_name) == 0)
			break;
	if (p->t_name == 0) {
		printf("%s: unknown mode\n", argv[1]);
		(void) fflush(stdout);
		code = -1;
		return;
	}
	if ((p->t_arg != NULL) && (*(p->t_arg) != '\0'))
		comret = command ("TYPE %s %s", p->t_mode, p->t_arg);
	else
		comret = command("TYPE %s", p->t_mode);
	if (comret == COMPLETE) {
		(void) strcpy(typename, p->t_name);
		type = p->t_type;
	}
}