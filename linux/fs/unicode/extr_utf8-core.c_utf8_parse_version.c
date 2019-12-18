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
typedef  int /*<<< orphan*/  version_string ;
typedef  int /*<<< orphan*/  substring_t ;
struct match_token {int member_0; char* member_1; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ match_int (int /*<<< orphan*/ *,unsigned int*) ; 
 int match_token (char*,struct match_token const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static int utf8_parse_version(const char *version, unsigned int *maj,
			      unsigned int *min, unsigned int *rev)
{
	substring_t args[3];
	char version_string[12];
	static const struct match_token token[] = {
		{1, "%d.%d.%d"},
		{0, NULL}
	};

	strncpy(version_string, version, sizeof(version_string));

	if (match_token(version_string, token, args) != 1)
		return -EINVAL;

	if (match_int(&args[0], maj) || match_int(&args[1], min) ||
	    match_int(&args[2], rev))
		return -EINVAL;

	return 0;
}