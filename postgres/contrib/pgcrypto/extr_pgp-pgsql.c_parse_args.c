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
typedef  int /*<<< orphan*/  uint8 ;
struct debug_expect {int dummy; } ;
typedef  int /*<<< orphan*/  PGP_Context ;

/* Variables and functions */
 int PXE_ARGUMENT_ERROR ; 
 char* downcase_convert (int /*<<< orphan*/ *,int) ; 
 char* getword (char*,char**,int*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int set_arg (int /*<<< orphan*/ *,char*,char*,struct debug_expect*) ; 

__attribute__((used)) static int
parse_args(PGP_Context *ctx, uint8 *args, int arg_len,
		   struct debug_expect *ex)
{
	char	   *str = downcase_convert(args, arg_len);
	char	   *key,
			   *val;
	int			key_len,
				val_len;
	int			res = 0;
	char	   *p = str;

	while (*p)
	{
		res = PXE_ARGUMENT_ERROR;
		p = getword(p, &key, &key_len);
		if (*p++ != '=')
			break;
		p = getword(p, &val, &val_len);
		if (*p == '\0')
			;
		else if (*p++ != ',')
			break;

		if (*key == 0 || *val == 0 || val_len == 0)
			break;

		key[key_len] = 0;
		val[val_len] = 0;

		res = set_arg(ctx, key, val, ex);
		if (res < 0)
			break;
	}
	pfree(str);
	return res;
}