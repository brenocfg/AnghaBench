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
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entity_idx ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  out_path ; 

__attribute__((used)) static void oseama_extract_parse_options(int argc, char **argv) {
	int c;

	while ((c = getopt(argc, argv, "e:o:")) != -1) {
		switch (c) {
		case 'e':
			entity_idx = atoi(optarg);
			break;
		case 'o':
			out_path = optarg;
			break;
		}
	}
}