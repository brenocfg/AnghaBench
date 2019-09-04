#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_bool ;
struct TYPE_11__ {int /*<<< orphan*/ * member_0; } ;
struct TYPE_10__ {int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_12__ {int /*<<< orphan*/  key; TYPE_2__ member_1; TYPE_1__ member_0; } ;
typedef  TYPE_3__ line_type ;
typedef  int /*<<< orphan*/  key_type ;
struct TYPE_13__ {int /*<<< orphan*/  fp; } ;
typedef  TYPE_4__ inifile ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int inifile_key_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  inifile_line_free (TYPE_3__*) ; 
 scalar_t__ inifile_read (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 int php_stream_copy_to_stream_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_seek (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 size_t php_stream_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inifile_filter(inifile *dba, inifile *from, const key_type *key, zend_bool *found)
{
	size_t pos_start = 0, pos_next = 0, pos_curr;
	int ret = SUCCESS;
	line_type ln = {{NULL,NULL},{NULL}};

	php_stream_seek(from->fp, 0, SEEK_SET);
	php_stream_seek(dba->fp, 0, SEEK_END);
	while(inifile_read(from, &ln)) {
		switch(inifile_key_cmp(&ln.key, key)) {
		case 0:
			if (found) {
				*found = (zend_bool) 1;
			}
			pos_curr = php_stream_tell(from->fp);
			if (pos_start != pos_next) {
				php_stream_seek(from->fp, pos_start, SEEK_SET);
				if (SUCCESS != php_stream_copy_to_stream_ex(from->fp, dba->fp, pos_next - pos_start, NULL)) {
					php_error_docref(NULL, E_WARNING, "Could not copy [%zu - %zu] from temporary stream", pos_next, pos_start);
					ret = FAILURE;
				}
				php_stream_seek(from->fp, pos_curr, SEEK_SET);
			}
			pos_next = pos_start = pos_curr;
			break;
		case 1:
			pos_next = php_stream_tell(from->fp);
			break;
		case 2:
			/* the function is meant to process only entries from same group */
			assert(0);
			break;
		}
	}
	if (pos_start != pos_next) {
		php_stream_seek(from->fp, pos_start, SEEK_SET);
		if (SUCCESS != php_stream_copy_to_stream_ex(from->fp, dba->fp, pos_next - pos_start, NULL)) {
			php_error_docref(NULL, E_WARNING, "Could not copy [%zu - %zu] from temporary stream", pos_next, pos_start);
			ret = FAILURE;
		}
	}
	inifile_line_free(&ln);
	return ret;
}