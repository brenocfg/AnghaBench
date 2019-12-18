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
 int getopt (int,char**,char*) ; 
 void* optarg ; 
 void* out_path ; 
 void* partition_name ; 

__attribute__((used)) static void osafeloader_extract_parse_options(int argc, char **argv) {
	int c;

	while ((c = getopt(argc, argv, "p:o:")) != -1) {
		switch (c) {
		case 'p':
			partition_name = optarg;
			break;
		case 'o':
			out_path = optarg;
			break;
		}
	}
}