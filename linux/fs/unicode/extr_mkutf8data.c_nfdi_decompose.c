#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int* utf32nfdi; unsigned int* utf32nfdicf; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (unsigned int*) ; 
 unsigned int* malloc (int) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned int*,int) ; 
 int /*<<< orphan*/  print_utf32nfdi (unsigned int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* unicode_data ; 
 int verbose ; 

__attribute__((used)) static void nfdi_decompose(void)
{
	unsigned int unichar;
	unsigned int mapping[19]; /* Magic - guaranteed not to be exceeded. */
	unsigned int *um;
	unsigned int *dc;
	int count;
	int i;
	int j;
	int ret;

	if (verbose > 0)
		printf("Decomposing nfdi\n");

	count = 0;
	for (unichar = 0; unichar != 0x110000; unichar++) {
		if (!unicode_data[unichar].utf32nfdi)
			continue;
		for (;;) {
			ret = 1;
			i = 0;
			um = unicode_data[unichar].utf32nfdi;
			while (*um) {
				dc = unicode_data[*um].utf32nfdi;
				if (dc) {
					for (j = 0; dc[j]; j++)
						mapping[i++] = dc[j];
					ret = 0;
				} else {
					mapping[i++] = *um;
				}
				um++;
			}
			mapping[i++] = 0;
			if (ret)
				break;
			free(unicode_data[unichar].utf32nfdi);
			um = malloc(i * sizeof(unsigned int));
			memcpy(um, mapping, i * sizeof(unsigned int));
			unicode_data[unichar].utf32nfdi = um;
		}
		/* Add this decomposition to nfdicf if there is no entry. */
		if (!unicode_data[unichar].utf32nfdicf) {
			um = malloc(i * sizeof(unsigned int));
			memcpy(um, mapping, i * sizeof(unsigned int));
			unicode_data[unichar].utf32nfdicf = um;
		}
		if (verbose > 1)
			print_utf32nfdi(unichar);
		count++;
	}
	if (verbose > 0)
		printf("Processed %d entries\n", count);
}