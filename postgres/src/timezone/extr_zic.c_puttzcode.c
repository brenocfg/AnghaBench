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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  convert (int /*<<< orphan*/  const,char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ * const) ; 

__attribute__((used)) static void
puttzcode(const int32 val, FILE *const fp)
{
	char		buf[4];

	convert(val, buf);
	fwrite(buf, sizeof buf, 1, fp);
}