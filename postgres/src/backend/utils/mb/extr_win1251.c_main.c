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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 

main()
{
	int			i;
	char		koitab[128],
				wintab[128];
	char		buf[4096];
	int			koi,
				win;

	for (i = 0; i < 128; i++)
		koitab[i] = wintab[i] = 0;

	while (fgets(buf, sizeof(buf), stdin) != NULL)
	{
		if (*buf == '#')
			continue;
		sscanf(buf, "%d %d", &koi, &win);
		if (koi < 128 || koi > 255 || win < 128 || win > 255)
		{
			fprintf(stderr, "invalid value %d\n", koi);
			exit(1);
		}
		koitab[koi - 128] = win;
		wintab[win - 128] = koi;
	}

	i = 0;
	printf("static char koi2win[] = {\n");
	while (i < 128)
	{
		int			j = 0;

		while (j < 8)
		{
			printf("0x%02x", koitab[i++]);
			j++;
			if (i >= 128)
				break;
			printf(", ");
		}
		printf("\n");
	}
	printf("};\n");

	i = 0;
	printf("static char win2koi[] = {\n");
	while (i < 128)
	{
		int			j = 0;

		while (j < 8)
		{
			printf("0x%02x", wintab[i++]);
			j++;
			if (i >= 128)
				break;
			printf(", ");
		}
		printf("\n");
	}
	printf("};\n");
}