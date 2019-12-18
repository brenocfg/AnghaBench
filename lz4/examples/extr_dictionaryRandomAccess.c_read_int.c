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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 size_t fread (int*,int,int,int /*<<< orphan*/ *) ; 

void read_int(FILE* fp, int* i) {
    size_t read = fread(i, sizeof(*i), 1, fp);
    if (read != 1) { exit(12); }
}