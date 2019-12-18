#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_bool ;
struct TYPE_18__ {char* value; } ;
typedef  TYPE_1__ val_type ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_19__ {scalar_t__ name; scalar_t__ group; } ;
typedef  TYPE_2__ key_type ;
struct TYPE_20__ {int /*<<< orphan*/ * fp; } ;
typedef  TYPE_3__ inifile ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 int /*<<< orphan*/  PHP_STREAM_COPY_ALL ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int inifile_copy_to (TYPE_3__*,size_t,size_t,TYPE_3__**) ; 
 int inifile_filter (TYPE_3__*,TYPE_3__*,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inifile_find_group (TYPE_3__*,TYPE_2__ const*,size_t*) ; 
 int /*<<< orphan*/  inifile_free (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inifile_next_group (TYPE_3__*,TYPE_2__ const*,size_t*) ; 
 int inifile_truncate (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  php_stream_close (int /*<<< orphan*/ *) ; 
 int php_stream_copy_to_stream_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_printf (int /*<<< orphan*/ *,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  php_stream_seek (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ php_stream_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_stream_temp_create (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (scalar_t__) ; 
 int /*<<< orphan*/  zend_throw_error (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int inifile_delete_replace_append(inifile *dba, const key_type *key, const val_type *value, int append, zend_bool *found)
{
	size_t pos_grp_start=0, pos_grp_next;
	inifile *ini_tmp = NULL;
	php_stream *fp_tmp = NULL;
	int ret;

	/* 1) Search group start
	 * 2) Search next group
	 * 3) If not append: Copy group to ini_tmp
	 * 4) Open temp_stream and copy remainder
	 * 5) Truncate stream
	 * 6) If not append AND key.name given: Filtered copy back from ini_tmp
	 *    to stream. Otherwise the user wanted to delete the group.
	 * 7) Append value if given
	 * 8) Append temporary stream
	 */

	assert(!append || (key->name && value)); /* missuse */

	/* 1 - 3 */
	inifile_find_group(dba, key, &pos_grp_start);
	inifile_next_group(dba, key, &pos_grp_next);
	if (append) {
		ret = SUCCESS;
	} else {
		ret = inifile_copy_to(dba, pos_grp_start, pos_grp_next, &ini_tmp);
	}

	/* 4 */
	if (ret == SUCCESS) {
		fp_tmp = php_stream_temp_create(0, 64 * 1024);
		if (!fp_tmp) {
			php_error_docref(NULL, E_WARNING, "Could not create temporary stream");
			ret = FAILURE;
		} else {
			php_stream_seek(dba->fp, 0, SEEK_END);
			if (pos_grp_next != (size_t)php_stream_tell(dba->fp)) {
				php_stream_seek(dba->fp, pos_grp_next, SEEK_SET);
				if (SUCCESS != php_stream_copy_to_stream_ex(dba->fp, fp_tmp, PHP_STREAM_COPY_ALL, NULL)) {
					php_error_docref(NULL, E_WARNING, "Could not copy remainder to temporary stream");
					ret = FAILURE;
				}
			}
		}
	}

	/* 5 */
	if (ret == SUCCESS) {
		if (!value || (key->name && strlen(key->name))) {
			ret = inifile_truncate(dba, append ? pos_grp_next : pos_grp_start); /* writes error on fail */
		}
	}

	if (ret == SUCCESS) {
		if (key->name && strlen(key->name)) {
			/* 6 */
			if (!append && ini_tmp) {
				ret = inifile_filter(dba, ini_tmp, key, found);
			}

			/* 7 */
			/* important: do not query ret==SUCCESS again: inifile_filter might fail but
			 * however next operation must be done.
			 */
			if (value) {
				if (pos_grp_start == pos_grp_next && key->group && strlen(key->group)) {
					php_stream_printf(dba->fp, "[%s]\n", key->group);
				}
				php_stream_printf(dba->fp, "%s=%s\n", key->name, value->value ? value->value : "");
			}
		}

		/* 8 */
		/* important: do not query ret==SUCCESS again: inifile_filter might fail but
		 * however next operation must be done.
		 */
		if (fp_tmp && php_stream_tell(fp_tmp)) {
			php_stream_seek(fp_tmp, 0, SEEK_SET);
			php_stream_seek(dba->fp, 0, SEEK_END);
			if (SUCCESS != php_stream_copy_to_stream_ex(fp_tmp, dba->fp, PHP_STREAM_COPY_ALL, NULL)) {
				zend_throw_error(NULL, "Could not copy from temporary stream - ini file truncated");
				ret = FAILURE;
			}
		}
	}

	if (ini_tmp) {
		php_stream_close(ini_tmp->fp);
		inifile_free(ini_tmp, 0);
	}
	if (fp_tmp) {
		php_stream_close(fp_tmp);
	}
	php_stream_flush(dba->fp);
	php_stream_seek(dba->fp, 0, SEEK_SET);

	return ret;
}