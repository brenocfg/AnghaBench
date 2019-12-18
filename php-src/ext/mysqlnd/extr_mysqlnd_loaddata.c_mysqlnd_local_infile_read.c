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
typedef  int /*<<< orphan*/  zend_uchar ;
struct TYPE_2__ {int /*<<< orphan*/  error_no; int /*<<< orphan*/  error_msg; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ MYSQLND_INFILE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CR_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_RETURN (int) ; 
 scalar_t__ php_stream_read (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static
int mysqlnd_local_infile_read(void * ptr, zend_uchar * buf, unsigned int buf_len)
{
	MYSQLND_INFILE_INFO	*info = (MYSQLND_INFILE_INFO *)ptr;
	int count;

	DBG_ENTER("mysqlnd_local_infile_read");

	count = (int) php_stream_read(info->fd, (char *) buf, buf_len);

	if (count < 0) {
		strcpy(info->error_msg, "Error reading file");
		info->error_no = CR_UNKNOWN_ERROR;
	}

	DBG_RETURN(count);
}