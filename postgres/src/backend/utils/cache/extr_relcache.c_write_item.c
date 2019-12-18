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
typedef  int /*<<< orphan*/  len ;
typedef  int Size ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int fwrite (void const*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
write_item(const void *data, Size len, FILE *fp)
{
	if (fwrite(&len, 1, sizeof(len), fp) != sizeof(len))
		elog(FATAL, "could not write init file");
	if (fwrite(data, 1, len, fp) != len)
		elog(FATAL, "could not write init file");
}