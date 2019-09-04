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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct phy_dm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int MAX_ARGC ; 
 int MAX_ARGV ; 
 int /*<<< orphan*/  phydm_cmd_parser (struct phy_dm_struct*,char**,int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char* strsep (char**,char*) ; 

s32 phydm_cmd(struct phy_dm_struct *dm, char *input, u32 in_len, u8 flag,
	      char *output, u32 out_len)
{
	char *token;
	u32 argc = 0;
	char argv[MAX_ARGC][MAX_ARGV];

	do {
		token = strsep(&input, ", ");
		if (token) {
			strcpy(argv[argc], token);
			argc++;
		} else {
			break;
		}
	} while (argc < MAX_ARGC);

	if (argc == 1)
		argv[0][strlen(argv[0]) - 1] = '\0';

	phydm_cmd_parser(dm, argv, argc, flag, output, out_len);

	return 0;
}