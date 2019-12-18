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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 long lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* malloc (long) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,char*,long) ; 

__attribute__((used)) static char *slurp(const char *file) {
	int ret, fd;
	char *text;
	long sz;
	if (!file || !*file)
		return NULL;
	fd = open (file, O_RDONLY);
	if (fd == -1) {
		return NULL;
	}
	sz = lseek (fd, 0, SEEK_END);
	if (sz < 0){
		close (fd);
		return NULL;
	}
	lseek (fd, 0, SEEK_SET);
	text = malloc (sz + 1);
	if (!text) {
		close (fd);
		return NULL;
	}
	ret = read (fd, text, sz);
	if (ret != sz) {
		free (text);
		text = NULL;
	} else {
		text[sz] = 0;
	}
	close (fd);
	return text;
}