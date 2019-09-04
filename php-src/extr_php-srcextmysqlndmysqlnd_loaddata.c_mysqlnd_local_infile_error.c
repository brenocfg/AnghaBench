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
struct TYPE_2__ {char* error_msg; int /*<<< orphan*/  error_no; } ;
typedef  TYPE_1__ MYSQLND_INFILE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CR_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_INF_FMT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,unsigned int) ; 

__attribute__((used)) static
int	mysqlnd_local_infile_error(void * ptr, char *error_buf, unsigned int error_buf_len)
{
	MYSQLND_INFILE_INFO	*info = (MYSQLND_INFILE_INFO *)ptr;

	DBG_ENTER("mysqlnd_local_infile_error");

	if (info) {
		strlcpy(error_buf, info->error_msg, error_buf_len);
		DBG_INF_FMT("have info, %d", info->error_no);
		DBG_RETURN(info->error_no);
	}

	strlcpy(error_buf, "Unknown error", error_buf_len);
	DBG_INF_FMT("no info, %d", CR_UNKNOWN_ERROR);
	DBG_RETURN(CR_UNKNOWN_ERROR);
}