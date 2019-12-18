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
 size_t fwrite (void const*,int,size_t,int /*<<< orphan*/ *) ; 

void write_bin(FILE* fp, const void* array, size_t arrayBytes) {
    size_t written = fwrite(array, 1, arrayBytes, fp);
    if (written != arrayBytes) { exit(11); }
}