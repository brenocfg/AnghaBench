#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {void* value; } ;
struct TYPE_11__ {char* name; void* group; } ;
struct TYPE_8__ {void* pos; TYPE_3__ val; TYPE_7__ key; } ;
typedef  TYPE_1__ line_type ;
struct TYPE_9__ {int /*<<< orphan*/  fp; } ;
typedef  TYPE_2__ inifile ;

/* Variables and functions */
 int /*<<< orphan*/  efree (char*) ; 
 void* estrdup (char*) ; 
 void* etrim (char*) ; 
 int /*<<< orphan*/  inifile_key_free (TYPE_7__*) ; 
 int /*<<< orphan*/  inifile_line_free (TYPE_1__*) ; 
 int /*<<< orphan*/  inifile_val_free (TYPE_3__*) ; 
 char* php_stream_gets (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* php_stream_tell (int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int inifile_read(inifile *dba, line_type *ln) {
	char *fline;
	char *pos;

	inifile_val_free(&ln->val);
	while ((fline = php_stream_gets(dba->fp, NULL, 0)) != NULL) {
		if (fline) {
			if (fline[0] == '[') {
				/* A value name cannot start with '['
				 * So either we find a ']' or we found an error
				 */
				pos = strchr(fline+1, ']');
				if (pos) {
					*pos = '\0';
					inifile_key_free(&ln->key);
					ln->key.group = etrim(fline+1);
					ln->key.name = estrdup("");
					ln->pos = php_stream_tell(dba->fp);
					efree(fline);
					return 1;
				} else {
					efree(fline);
					continue;
				}
			} else {
				pos = strchr(fline, '=');
				if (pos) {
					*pos = '\0';
					/* keep group or make empty if not existent */
					if (!ln->key.group) {
						ln->key.group = estrdup("");
					}
					if (ln->key.name) {
						efree(ln->key.name);
					}
					ln->key.name = etrim(fline);
					ln->val.value = etrim(pos+1);
					ln->pos = php_stream_tell(dba->fp);
					efree(fline);
					return 1;
				} else {
					/* simply ignore lines without '='
					 * those should be comments
					 */
					 efree(fline);
					 continue;
				}
			}
		}
	}
	inifile_line_free(ln);
	return 0;
}