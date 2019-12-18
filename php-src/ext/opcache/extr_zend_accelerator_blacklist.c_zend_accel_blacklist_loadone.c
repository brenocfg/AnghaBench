#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t pos; TYPE_1__* entries; } ;
typedef  TYPE_2__ zend_blacklist ;
typedef  int /*<<< orphan*/  real_path ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {int path_length; char* path; size_t id; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEL_LOG_DEBUG ; 
 int /*<<< orphan*/  ACCEL_LOG_ERROR ; 
 int /*<<< orphan*/  ACCEL_LOG_WARNING ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 scalar_t__ VCWD_REALPATH (char*,char*) ; 
 int /*<<< orphan*/  expand_filepath (char*,char*) ; 
 int /*<<< orphan*/  expand_filepath_ex (char*,char*,char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  zend_accel_blacklist_allocate (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_accel_error (int /*<<< orphan*/ ,char*,...) ; 
 int zend_dirname (char*,int) ; 
 char* zend_strndup (char*,int) ; 

__attribute__((used)) static void zend_accel_blacklist_loadone(zend_blacklist *blacklist, char *filename)
{
	char buf[MAXPATHLEN + 1], real_path[MAXPATHLEN + 1], *blacklist_path = NULL;
	FILE *fp;
	int path_length, blacklist_path_length;

	if ((fp = fopen(filename, "r")) == NULL) {
		zend_accel_error(ACCEL_LOG_WARNING, "Cannot load blacklist file: %s\n", filename);
		return;
	}

	zend_accel_error(ACCEL_LOG_DEBUG,"Loading blacklist file:  '%s'", filename);

	if (VCWD_REALPATH(filename, buf)) {
		blacklist_path_length = zend_dirname(buf, strlen(buf));
		blacklist_path = zend_strndup(buf, blacklist_path_length);
	}

	memset(buf, 0, sizeof(buf));
	memset(real_path, 0, sizeof(real_path));

	while (fgets(buf, MAXPATHLEN, fp) != NULL) {
		char *path_dup, *pbuf;
		path_length = strlen(buf);
		if (path_length > 0 && buf[path_length - 1] == '\n') {
			buf[--path_length] = 0;
			if (path_length > 0 && buf[path_length - 1] == '\r') {
				buf[--path_length] = 0;
			}
		}

		/* Strip ctrl-m prefix */
		pbuf = &buf[0];
		while (*pbuf == '\r') {
			*pbuf++ = 0;
			path_length--;
		}

		/* strip \" */
		if (pbuf[0] == '\"' && pbuf[path_length - 1]== '\"') {
			*pbuf++ = 0;
			path_length -= 2;
		}

		if (path_length == 0) {
			continue;
		}

		/* skip comments */
		if (pbuf[0]==';') {
			continue;
		}

		path_dup = zend_strndup(pbuf, path_length);
		if (blacklist_path) {
			expand_filepath_ex(path_dup, real_path, blacklist_path, blacklist_path_length);
		} else {
			expand_filepath(path_dup, real_path);
		}
		path_length = strlen(real_path);

		free(path_dup);

		zend_accel_blacklist_allocate(blacklist);
		blacklist->entries[blacklist->pos].path_length = path_length;
		blacklist->entries[blacklist->pos].path = (char *)malloc(path_length + 1);
		if (!blacklist->entries[blacklist->pos].path) {
			zend_accel_error(ACCEL_LOG_ERROR, "malloc() failed\n");
			fclose(fp);
			return;
		}
		blacklist->entries[blacklist->pos].id = blacklist->pos;
		memcpy(blacklist->entries[blacklist->pos].path, real_path, path_length + 1);
		blacklist->pos++;
	}
	fclose(fp);
	if (blacklist_path) {
		free(blacklist_path);
	}
}