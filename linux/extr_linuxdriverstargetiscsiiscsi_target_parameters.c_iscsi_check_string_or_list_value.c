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
struct iscsi_param {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAP ; 
 int /*<<< orphan*/  CRC32C ; 
 int /*<<< orphan*/  DISCOVERY ; 
 scalar_t__ IS_PSTATE_PROPOSER (struct iscsi_param*) ; 
 scalar_t__ IS_TYPERANGE_AUTH_PARAM (struct iscsi_param*) ; 
 scalar_t__ IS_TYPERANGE_DIGEST_PARAM (struct iscsi_param*) ; 
 scalar_t__ IS_TYPERANGE_SESSIONTYPE (struct iscsi_param*) ; 
 int /*<<< orphan*/  KRB5 ; 
 int /*<<< orphan*/  NONE ; 
 int /*<<< orphan*/  NORMAL ; 
 int /*<<< orphan*/  SPKM1 ; 
 int /*<<< orphan*/  SPKM2 ; 
 int /*<<< orphan*/  SRP ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsi_check_string_or_list_value(struct iscsi_param *param, char *value)
{
	if (IS_PSTATE_PROPOSER(param))
		return 0;

	if (IS_TYPERANGE_AUTH_PARAM(param)) {
		if (strcmp(value, KRB5) && strcmp(value, SPKM1) &&
		    strcmp(value, SPKM2) && strcmp(value, SRP) &&
		    strcmp(value, CHAP) && strcmp(value, NONE)) {
			pr_err("Illegal value for \"%s\", must be"
				" \"%s\", \"%s\", \"%s\", \"%s\", \"%s\""
				" or \"%s\".\n", param->name, KRB5,
					SPKM1, SPKM2, SRP, CHAP, NONE);
			return -1;
		}
	}
	if (IS_TYPERANGE_DIGEST_PARAM(param)) {
		if (strcmp(value, CRC32C) && strcmp(value, NONE)) {
			pr_err("Illegal value for \"%s\", must be"
				" \"%s\" or \"%s\".\n", param->name,
					CRC32C, NONE);
			return -1;
		}
	}
	if (IS_TYPERANGE_SESSIONTYPE(param)) {
		if (strcmp(value, DISCOVERY) && strcmp(value, NORMAL)) {
			pr_err("Illegal value for \"%s\", must be"
				" \"%s\" or \"%s\".\n", param->name,
					DISCOVERY, NORMAL);
			return -1;
		}
	}

	return 0;
}