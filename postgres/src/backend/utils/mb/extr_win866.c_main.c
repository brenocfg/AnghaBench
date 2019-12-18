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
				alttab[128];
	char		buf[4096];
	int			koi,
				alt;

	for (i = 0; i < 128; i++)
		koitab[i] = alttab[i] = 0;

	while (fgets(buf, sizeof(buf), stdin) != NULL)
	{
		if (*buf == '#')
			continue;
		sscanf(buf, "%d %d", &koi, &alt);
		if (koi < 128 || koi > 255 || alt < 128 || alt > 255)
		{
			fprintf(stderr, "invalid value %d\n", koi);
			exit(1);
		}
		koitab[koi - 128] = alt;
		alttab[alt - 128] = koi;
	}

	i = 0;
	printf("static char koi2alt[] = {\n");
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
	printf("static char alt2koi[] = {\n");
	while (i < 128)
	{
		int			j = 0;

		while (j < 8)
		{
			printf("0x%02x", alttab[i++]);
			j++;
			if (i >= 128)
				break;
			printf(", ");
		}
		printf("\n");
	}
	printf("};\n");
}