#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zend_bool ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {scalar_t__ s; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ smart_str ;
typedef  int /*<<< orphan*/  MYSQL ;

/* Variables and functions */
 char* ZSTR_VAL (scalar_t__) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int mysql_real_query (int /*<<< orphan*/ *,char*,size_t) ; 
 char* mysqli_escape_string_for_tx_name_in_comment (char const* const) ; 
 int /*<<< orphan*/  mysqli_tx_cor_options_to_string (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  smart_str_0 (TYPE_1__*) ; 
 int /*<<< orphan*/  smart_str_free (TYPE_1__*) ; 
 size_t spprintf (char**,int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static int mysqli_commit_or_rollback_libmysql(MYSQL * conn, zend_bool commit, const uint32_t mode, const char * const name)
{
	int ret;
	smart_str tmp_str = {0};
	mysqli_tx_cor_options_to_string(conn, &tmp_str, mode);
	smart_str_0(&tmp_str);

	{
		char *query;
		char *name_esc = mysqli_escape_string_for_tx_name_in_comment(name);
		size_t query_len;

		query_len = spprintf(&query, 0,
				(commit? "COMMIT%s %s":"ROLLBACK%s %s"), name_esc? name_esc:"", tmp_str.s? ZSTR_VAL(tmp_str.s):"");
		smart_str_free(&tmp_str);
		if (name_esc) {
			efree(name_esc);
			name_esc = NULL;
		}

		ret = mysql_real_query(conn, query, query_len);
		efree(query);
	}
	return ret;
}