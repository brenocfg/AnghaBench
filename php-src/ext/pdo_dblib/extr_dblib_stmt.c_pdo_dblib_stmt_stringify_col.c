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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int DBINT ;
typedef  char DBCHAR ;

/* Variables and functions */
 int DATETIME_MAX_LEN ; 
 int /*<<< orphan*/  SQLCHAR ; 
#define  SQLDATETIM4 129 
#define  SQLDATETIME 128 
 int /*<<< orphan*/  ZVAL_EMPTY_STRING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int) ; 
 int dbconvert (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  efree (char*) ; 
 void* emalloc (int) ; 

__attribute__((used)) static void pdo_dblib_stmt_stringify_col(int coltype, LPBYTE data, DBINT data_len, zval **ptr)
{
	DBCHAR *tmp_data;
	DBINT tmp_data_len;
	zval *zv;

	/* FIXME: We allocate more than we need here */
	tmp_data_len = 32 + (2 * (data_len));

	switch (coltype) {
		case SQLDATETIME:
		case SQLDATETIM4: {
			if (tmp_data_len < DATETIME_MAX_LEN) {
				tmp_data_len = DATETIME_MAX_LEN;
			}
			break;
		}
	}

	tmp_data = emalloc(tmp_data_len);
	data_len = dbconvert(NULL, coltype, data, data_len, SQLCHAR, (LPBYTE) tmp_data, tmp_data_len);

	zv = emalloc(sizeof(zval));
	if (data_len > 0) {
		/* to prevent overflows, tmp_data_len is provided as a dest len for dbconvert()
		 * this code previously passed a dest len of -1
		 * the FreeTDS impl of dbconvert() does an rtrim with that value, so replicate that behavior
		 */
		while (data_len > 0 && tmp_data[data_len - 1] == ' ') {
			data_len--;
		}

		ZVAL_STRINGL(zv, tmp_data, data_len);
	} else {
		ZVAL_EMPTY_STRING(zv);
	}

	efree(tmp_data);

	*ptr = zv;
}