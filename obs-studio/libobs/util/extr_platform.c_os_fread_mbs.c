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
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  bfree (char*) ; 
 char* bmalloc (size_t) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ os_ftelli64 (int /*<<< orphan*/ *) ; 
 size_t os_mbs_to_utf8_ptr (char*,size_t,char**) ; 

size_t os_fread_mbs(FILE *file, char **pstr)
{
	size_t size = 0;
	size_t len = 0;

	fseek(file, 0, SEEK_END);
	size = (size_t)os_ftelli64(file);
	*pstr = NULL;

	if (size > 0) {
		char *mbstr = bmalloc(size + 1);

		fseek(file, 0, SEEK_SET);
		size = fread(mbstr, 1, size, file);
		if (size == 0) {
			bfree(mbstr);
			return 0;
		}

		mbstr[size] = 0;
		len = os_mbs_to_utf8_ptr(mbstr, size, pstr);
		bfree(mbstr);
	}

	return len;
}