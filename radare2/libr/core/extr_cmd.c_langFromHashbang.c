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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  firstLine ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  r_sandbox_close (int) ; 
 int r_sandbox_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int r_sandbox_read (int,int /*<<< orphan*/ *,int) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static char *langFromHashbang(RCore *core, const char *file) {
	int fd = r_sandbox_open (file, O_RDONLY, 0);
	if (fd != -1) {
		char firstLine[128] = {0};
		int len = r_sandbox_read (fd, (ut8*)firstLine, sizeof (firstLine) - 1);
		firstLine[len] = 0;
		if (!strncmp (firstLine, "#!/", 3)) {
			// I CAN HAS A HASHBANG
			char *nl = strchr (firstLine, '\n');
			if (nl) {
				*nl = 0;
			}
			nl = strchr (firstLine, ' ');
			if (nl) {
				*nl = 0;
			}
			return strdup (firstLine + 2);
		}
		r_sandbox_close (fd);
	}
	return NULL;
}