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
struct fdarray {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fdarray__fprintf (struct fdarray*,int /*<<< orphan*/ *) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int fdarray__fprintf_prefix(struct fdarray *fda, const char *prefix, FILE *fp)
{
	int printed = 0;

	if (verbose <= 0)
		return 0;

	printed += fprintf(fp, "\n%s: ", prefix);
	return printed + fdarray__fprintf(fda, fp);
}