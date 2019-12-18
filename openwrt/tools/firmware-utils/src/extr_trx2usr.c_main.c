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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int trx2usr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink (char*) ; 

extern	int	main(int argc, char *argv[])
{
	FILE*	in;
	FILE*	out;
	int	ret;

	if (argc != 3)
	{
		fprintf(stderr, "Usage: trx2usr <trx input> <usr output>\n");
		exit(2);
	}
	in  = fopen(argv[1], "rb");
	if (!in)
	{
		fprintf(stderr, "Cannot open \"%s\": %s\n", argv[1], strerror(errno));
		exit(1);
	}
	out = fopen(argv[2], "wb");
	if (!out)
	{
		fprintf(stderr, "Cannot create \"%s\": %s\n", argv[2], strerror(errno));
		exit(1);
	}
	ret = trx2usr(in, out);
	fclose(in);
	fclose(out);
	if (ret)
	{
		unlink(argv[2]);
	}
	return ret;
}