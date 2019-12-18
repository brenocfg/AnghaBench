#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ output_type; } ;
typedef  TYPE_1__ TCCState ;

/* Variables and functions */
 int AFF_PREPROCESS ; 
 int AFF_PRINT_ERROR ; 
 scalar_t__ TCC_OUTPUT_PREPROCESS ; 
 int /*<<< orphan*/  dirname ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int tcc_add_file_internal (TYPE_1__*,char const*,int) ; 

int tcc_add_file(TCCState *s, const char *filename, const char *directory)
{
	if (directory) {
		dirname = strdup (directory);
	}

	if (s->output_type == TCC_OUTPUT_PREPROCESS) {
		return tcc_add_file_internal (s, filename, AFF_PRINT_ERROR | AFF_PREPROCESS);
	} else {
		return tcc_add_file_internal (s, filename, AFF_PRINT_ERROR);
	}
}