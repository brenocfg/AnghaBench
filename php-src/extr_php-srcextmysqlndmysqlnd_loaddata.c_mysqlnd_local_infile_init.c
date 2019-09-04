#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  php_stream_context ;
struct TYPE_2__ {char* filename; int /*<<< orphan*/  error_no; scalar_t__ error_msg; int /*<<< orphan*/ * fd; } ;
typedef  TYPE_1__ MYSQLND_INFILE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CR_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_RETURN (int) ; 
 int /*<<< orphan*/  MYSQLND_EE_FILENOTFOUND ; 
 scalar_t__ PG (int /*<<< orphan*/ ) ; 
 scalar_t__ mnd_ecalloc (int,int) ; 
 int /*<<< orphan*/  open_basedir ; 
 int php_check_open_basedir_ex (char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * php_stream_open_wrapper_ex (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const* const) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,char*) ; 

__attribute__((used)) static
int mysqlnd_local_infile_init(void ** ptr, const char * const filename)
{
	MYSQLND_INFILE_INFO	*info;
	php_stream_context	*context = NULL;

	DBG_ENTER("mysqlnd_local_infile_init");

	info = ((MYSQLND_INFILE_INFO *)mnd_ecalloc(1, sizeof(MYSQLND_INFILE_INFO)));
	if (!info) {
		DBG_RETURN(1);
	}

	*ptr = info;

	/* check open_basedir */
	if (PG(open_basedir)) {
		if (php_check_open_basedir_ex(filename, 0) == -1) {
			strcpy(info->error_msg, "open_basedir restriction in effect. Unable to open file");
			info->error_no = CR_UNKNOWN_ERROR;
			DBG_RETURN(1);
		}
	}

	info->filename = filename;
	info->fd = php_stream_open_wrapper_ex((char *)filename, "r", 0, NULL, context);

	if (info->fd == NULL) {
		snprintf((char *)info->error_msg, sizeof(info->error_msg), "Can't find file '%-.64s'.", filename);
		info->error_no = MYSQLND_EE_FILENOTFOUND;
		DBG_RETURN(1);
	}

	DBG_RETURN(0);
}