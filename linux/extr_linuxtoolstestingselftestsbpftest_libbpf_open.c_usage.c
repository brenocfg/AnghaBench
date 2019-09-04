#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; int val; } ;

/* Variables and functions */
 char* __doc__ ; 
 TYPE_1__* long_options ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void usage(char *argv[])
{
	int i;

	printf("\nDOCUMENTATION:\n%s\n\n", __doc__);
	printf(" Usage: %s (options-see-below) BPF_FILE\n", argv[0]);
	printf(" Listing options:\n");
	for (i = 0; long_options[i].name != 0; i++) {
		printf(" --%-12s", long_options[i].name);
		printf(" short-option: -%c",
		       long_options[i].val);
		printf("\n");
	}
	printf("\n");
}