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
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RFSRoot ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * fscmd (int /*<<< orphan*/ *,char*,float) ; 
 char* r_str_newf (char*,char const*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static RList *__flags(RFSRoot *root, const char *path) {
	const char *prefix = NULL;
	if (!strncmp (path, "/flags/", 7)) {
		prefix = path + 7;
	}
	char *cmd = prefix
		? r_str_newf ("fq@F:%s", prefix)
		: strdup ("fsq");
	RList *res = fscmd (root, cmd, prefix? 'f': 'd');
	free (cmd);
	return res;
}