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

/* Variables and functions */
 int /*<<< orphan*/  isalnum (char) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static void fill_pcm_stream_name(char *str, size_t len, const char *sfx,
				 const char *chip_name)
{
	char *p;

	if (*str)
		return;
	strlcpy(str, chip_name, len);

	/* drop non-alnum chars after a space */
	for (p = strchr(str, ' '); p; p = strchr(p + 1, ' ')) {
		if (!isalnum(p[1])) {
			*p = 0;
			break;
		}
	}
	strlcat(str, sfx, len);
}