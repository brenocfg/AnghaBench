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
typedef  int /*<<< orphan*/  RFSFile ;
typedef  int /*<<< orphan*/  RFS ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_fs_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_fs_file_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_fs_open (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  r_fs_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 char* r_str_newf (char*,char const*,char*) ; 
 int /*<<< orphan*/  r_str_trim (char*) ; 
 char* r_str_trim_dup (char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static bool handlePipes(RFS *fs, char *msg, const ut8 *data, const char *cwd) {
	char *red = strchr (msg, '>');
	if (red) {
		*red++ = 0;
		r_str_trim (msg);
		red = r_str_trim_dup (red);
		if (*red != '/') {
			char *blu = r_str_newf ("%s/%s", cwd, red);
			free (red);
			red = blu;
		} else {
		}
		RFSFile *f = r_fs_open (fs, red, true);
		if (!f) {
			eprintf ("Cannot open %s for writing\n", red);
			free (red);
			return true;
		}
		r_fs_write (fs, f, 0, data == NULL ? (const ut8 *) msg : data, strlen (msg));
		free (red);
		r_fs_close (fs, f);
		r_fs_file_free (f);
		return true;
	}
	return false;
}