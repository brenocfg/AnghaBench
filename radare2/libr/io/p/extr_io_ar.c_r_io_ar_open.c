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
typedef  int /*<<< orphan*/  RIODesc ;
typedef  int /*<<< orphan*/  RIO ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/ * ar_open_file (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * r_io_desc_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_io_plugin_ar ; 
 char* strdup (char const*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static RIODesc *r_io_ar_open(RIO *io, const char *file, int rw, int mode) {
	RIODesc *res = NULL;
	char *url = strdup (file);
	char *arname = strstr (url, "://") + 3;
	char *filename = strstr (arname, "//");
	if (filename) {
		*filename = 0;
		filename += 2;
	}

	RBuffer *b = ar_open_file (arname, filename);
	if (b) {
		res = r_io_desc_new (io, &r_io_plugin_ar, filename, rw, mode, b);
	}
	free (url);
	return res;
}